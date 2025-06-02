#include "AI.h"

#include <algorithm>
#include <iostream>

#include "Chess.h"
#include "easyx.h"
#include "game.h"
#include "GameStateStack.h"
#include "Go.h"
#include "Gomoku.h"
//
// Created by Administrator on 25-6-2.
//

extern GameStateStack _stack;
extern std::vector<Chess> chesses;
extern int chesscolor;

// 方向数组：上、右、右上、右下
const int dx[] = {0, 1, 1, 1};
const int dy[] = {1, 0, 1, -1};

bool isPositionEmpty(int x, int y) {
    for (const auto& chess : chesses) {
        if (chess.c_x == x && chess.c_y == y) {
            return false;
        }
    }
    return true;
}

void evaluateGomokuPosition(int &x, int &y) {
    if (chesses.empty()) {
        // 第一步下在中心
        x = GRID_N / 2;
        y = GRID_N / 2;
        return;
    }

    int bestScore = -1;
    std::vector<std::pair<int, int>> bestMoves;

    for (int i = 0; i < GRID_N; i++) {
        for (int j = 0; j < GRID_N; j++) {
            if (isPositionEmpty(i, j)) {
                // 进攻评分（当前玩家）
                int score = evaluatePosition(i, j, chesscolor);

                // 防守评分（对手）
                int opponentColor = (chesscolor == BLACK) ? WHITE : BLACK;
                score += evaluatePosition(i, j, opponentColor) * 0.8;

                if (score > bestScore) {
                    bestScore = score;
                    bestMoves.clear();
                    bestMoves.emplace_back(i, j);
                }
                else if (score == bestScore) {
                    bestMoves.emplace_back(i, j);
                }
            }
        }
    }

    // 随机选择最佳位置
    if (!bestMoves.empty()) {
        int index = rand() % bestMoves.size();
        x = bestMoves[index].first;
        y = bestMoves[index].second;
    } else {
        x = GRID_N / 2;
        y = GRID_N / 2;
    }
}

int evaluatePosition(int x, int y, int color) {
    int score = 0;

    for (int dir = 0; dir < 4; dir++) {
        int count = 1; // 当前位置
        bool blocked = false;

        // 正向检查
        for (int step = 1; step < 5; step++) {
            int nx = x + dx[dir] * step;
            int ny = y + dy[dir] * step;

            if (nx < 0 || nx >= GRID_N || ny < 0 || ny >= GRID_N) {
                blocked = true;
                break;
            }

            bool found = false;
            for (const auto& chess : chesses) {
                if (chess.c_x == nx && chess.c_y == ny) {
                    found = true;
                    if (chess.color == color) count++;
                    else blocked = true;
                    break;
                }
            }
            if (blocked || !found) break;
        }

        // 反向检查（相同逻辑）
        // ...（代码与正向检查对称）

        // 评分规则
        if (count >= 5) score += 100000;
        else if (count == 4 && !blocked) score += 10000;
        else if (count == 4 && blocked) score += 1000;
        else if (count == 3 && !blocked) score += 500;
        else if (count == 3 && blocked) score += 100;
        else if (count == 2 && !blocked) score += 50;
    }

    return score;
}

int distanceToNearestOpponent(int x, int y, int opponentColor) {
    int minDist = INT_MAX;
    for (const auto &chess : chesses) {
        if (chess.color == opponentColor) {
            int dist = abs(chess.c_x - x) + abs(chess.c_y - y);
            if (dist < minDist) minDist = dist;
        }
    }
    return (minDist == INT_MAX) ? 0 : minDist;
}

// 检查是否有气（简化版）
bool hasLiberty(int x, int y, int color) {
    const int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx >= 0 && nx < GRID_N && ny >= 0 && ny < GRID_N) {
            if (isPositionEmpty(nx, ny)) return true;
        }
    }
    return false;
}

// 简化版吃子检测
bool canCapture(int x, int y, int color) {
    const int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    int opponentColor = (color == BLACK) ? WHITE : BLACK;

    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx >= 0 && nx < GRID_N && ny >= 0 && ny < GRID_N) {
            for (auto &chess : chesses) {
                if (chess.c_x == nx && chess.c_y == ny && chess.color == opponentColor) {
                    if (!hasLiberty(nx, ny, opponentColor)) return true;
                }
            }
        }
    }
    return false;
}

// 自杀检测（落子后是否无气）
bool isSuicidal(int x, int y, int color) {
    // 临时模拟落子
    chesses.push_back(Chess(x, y, color));
    bool suicidal = !hasLiberty(x, y, color);
    chesses.pop_back();
    return suicidal;
}

int evaluateGoMove(int x, int y) {
    int score = 0;
    int opponentColor = (chesscolor == BLACK) ? WHITE : BLACK;

    // 1. 基础分：距离对手棋子的距离（越近越好）
    score += 100 - distanceToNearestOpponent(x, y, opponentColor);

    // 2. 气（liberty）检测（有气+50分）
    if (hasLiberty(x, y, chesscolor)) score += 50;

    // 3. 能吃子+200分
    if (canCapture(x, y, chesscolor)) score += 200;

    // 4. 避免自杀-100分
    if (isSuicidal(x, y, chesscolor)) score -= 100;

    return score;
}

void evaluateGoPosition(int &x, int &y) {
    // 第一步通常下在星位（坐标是3的倍数）
    if (chesses.empty()) {
        const int starPoints[] = {3, 9, 15}; // 适合18x18格子的星位
        x = starPoints[rand() % 3];
        y = starPoints[rand() % 3];
        return;
    }

    // 候选落子点（带评分）
    struct Move {
        int x, y;
        int score;
    };
    std::vector<Move> candidates;

    // 1. 基础评分：优先靠近敌方棋子
    for (int i = 0; i < GRID_N; i++) {
        for (int j = 0; j < GRID_N; j++) {
            if (isPositionEmpty(i, j)) {
                Move move;
                move.x = i;
                move.y = j;
                move.score = evaluateGoMove(i, j);
                candidates.push_back(move);
            }
        }
    }

    // 2. 按评分排序
    std::sort(candidates.begin(), candidates.end(), [](const Move &a, const Move &b) {
        return a.score > b.score;
    });

    // 3. 从Top5中随机选择（避免固定模式）
    if (!candidates.empty()) {
        int topN = std::min(5, (int)candidates.size());
        int selected = rand() % topN;
        x = candidates[selected].x;
        y = candidates[selected].y;
    } else {
        // 极端情况：没有合法位置（理论上不会发生）
        x = GRID_N / 2;
        y = GRID_N / 2;
    }
}

void AI::get_Chess_Position(int &x, int &y) {
    if (_stack.peekState() == "GOMOKU") {
        evaluateGomokuPosition(x, y);
    }
    else if (_stack.peekState() == "GO") {
        evaluateGoPosition(x, y);
    }
}//这里要写ai如何判断应该在哪里落子，落子后返回坐标

bool AI::put_Chess() {
    printf("1chesscolor addr: %p, value: %d\n", &chesscolor, chesscolor);
    Chess newchess = Chess(0, 0, BLACK);
    while (1) {
        //到底在哪里创建新棋子？(最终确定格子位置gx,gy=?）
        int gx;
        int gy;
        get_Chess_Position(gx, gy);
        std::cout << gx << " " << gy << std::endl;
        //将新棋子填入到chesses中
        newchess = Chess(gx, gy, chesscolor);
        printf("2chesscolor addr: %p, value: %d\n", &chesscolor, chesscolor);
        std::cout << gx << " " << gy << std::endl;
        if(!newchess.is_Chess_Exist(chesses)) {
            chesses.push_back(newchess);
            break;
        }
    }
    if (_stack.peekState() == "GOMOKU") {
        BeginBatchDraw();
        int result = gomoku_CheckWin(chesses, newchess);
        printf("3chesscolor addr: %p, value: %d\n", &chesscolor, chesscolor);
        std::cout << chesscolor<< std::endl;
        cleardevice();
        draw_Board();
        draw_Chess(chesses);
        EndBatchDraw();
        if (result != NORMAL_WIN) {
            return true; // 游戏结束，胜负已分
        }
    } else if (_stack.peekState() == "GO") {
        BeginBatchDraw();
        execute_Go_Rules();
        BeginBatchDraw();
        draw_Board();
        draw_Chess(chesses);
        int result = go_CheckWin(chesses, newchess);
        if (result != NORMAL_WIN) {
            return true;
        }
        EndBatchDraw();
    }
    printf("chesscolor addr: %p, value: %d\n", &chesscolor, chesscolor);
    // 切换玩家
        chesscolor = (chesscolor == BLACK) ? WHITE : BLACK;
}

AI::~AI() {

}

AI::AI() {

}


