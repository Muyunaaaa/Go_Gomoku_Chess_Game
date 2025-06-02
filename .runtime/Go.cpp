#include "Go.h"
#include "game.h"
#include "draw.h"
#include "easyx.h"
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>

#include "Chess.h"
#include "game.h"
#include <unordered_set>
struct PairHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

// 全局变量声明（在其他地方定义）
extern std::vector<Chess> chesses;

bool isWithinBoard(int grid_x, int grid_y) {
    return grid_x >= 0 && grid_x < BOARD_GRID_SIZE &&
           grid_y >= 0 && grid_y < BOARD_GRID_SIZE;
}

void getConnectedBlockAndLiberties(const std::vector<Chess>& chesses,
                                  const Chess& start,
                                  std::vector<Chess>& block,
                                  bool& hasLiberty) {
    std::unordered_set<std::pair<int, int>, PairHash> visited;
    std::queue<Chess> q;
    q.push(start);
    visited.insert({start.grid_x, start.grid_y});
    hasLiberty = false;

    while (!q.empty()) {
        Chess current = q.front();
        q.pop();
        block.push_back(current);

        for (const auto& dir : GRID_DIRECTIONS) {
            int nx = current.grid_x + dir[0];
            int ny = current.grid_y + dir[1];

            if (!isWithinBoard(nx, ny)) {
                // 边缘不算气（标准围棋规则）
                continue;
            }

            // 检查是否有棋子存在
            bool occupied = false;
            bool sameColor = false;
            for (const auto& c : chesses) {
                if (c.grid_x == nx && c.grid_y == ny) {
                    occupied = true;
                    if (c.color == start.color) {
                        sameColor = true;
                        if (visited.count({nx, ny}) == 0) {
                            q.push(c);
                            visited.insert({nx, ny});
                        }
                    }
                    break;
                }
            }

            if (!occupied) {
                hasLiberty = true; // 发现空位（气）
            }
        }
    }
}

void removeCapturedChesses(std::vector<Chess>& chesses, const Chess& lastChess) {
    std::unordered_set<std::pair<int, int>, PairHash> toRemove;

    for (const auto& dir : GRID_DIRECTIONS) {
        int nx = lastChess.grid_x + dir[0];
        int ny = lastChess.grid_y + dir[1];

        // 查找邻近敌方棋子
        for (auto it = chesses.begin(); it != chesses.end(); ++it) {
            if (it->grid_x == nx && it->grid_y == ny && it->color != lastChess.color) {
                std::vector<Chess> block;
                bool hasLiberty;
                getConnectedBlockAndLiberties(chesses, *it, block, hasLiberty);

                if (!hasLiberty) {
                    for (const auto& c : block) {
                        toRemove.insert({c.grid_x, c.grid_y});
                    }
                }
                break;
            }
        }
    }

    // 批量删除被围棋子
    chesses.erase(std::remove_if(chesses.begin(), chesses.end(),
        [&](const Chess& c) {
            return toRemove.count({c.grid_x, c.grid_y}) > 0;
        }),
        chesses.end());
}

void execute_Go_Rules() {
    std::cout << "Executing GO rules. Total chesses: " << chesses.size() << std::endl;
    if (chesses.empty()) return;
    Chess last = chesses.back();

    // 1. 提掉被围的敌方棋子
    removeCapturedChesses(chesses, last);

    // 2. 检查自身是否还有气（防止自杀）
    std::vector<Chess> selfBlock;
    bool selfHasLiberty = false;
    getConnectedBlockAndLiberties(chesses, last, selfBlock, selfHasLiberty);
    if (!selfHasLiberty) {
        // 自杀行为，撤回落子
        chesses.pop_back();
        // 你也可以在此处弹出提示，如：
        // MessageBox(NULL, _T("此处无气，不能落子"), _T("提示"), MB_OK);
    }
}

int go_CheckWin(const std::vector<Chess>& chesses, const Chess& lastChess) {
    bool blackExist = false, whiteExist = false;

    for (const auto& c : chesses) {
        if (c.color == BLACK) blackExist = true;
        if (c.color == WHITE) whiteExist = true;
    }

    // 如果当前棋子数少于 N（例如 4），不判断胜负
    if (chesses.size() < 4) return NORMAL_WIN;

    if (!blackExist) return WHITE_WIN;
    if (!whiteExist) return BLACK_WIN;

    return NORMAL_WIN;
}
