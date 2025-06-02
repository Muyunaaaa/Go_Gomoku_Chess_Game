//
// Created by 冯于洋 on 25-5-26.
//
#include "Gomuku.h"
#include "game.h"
#include "draw.h"
#include "easyx.h"
#include <algorithm>

#include "Chess.h"

// 通用的方向检查函数（可用于三、四、五连的判断）
bool gomuku_CheckDirection(const std::vector<Chess>& chesses, const Chess& lastChess, int dx, int dy, int countNeeded) {
    int count = 1; // 当前刚落下的棋子

    // 检查正方向
    for (int i = 1; i < countNeeded; i++) {
        int x = lastChess.c_x + i * dx * GRID_SIZE;
        int y = lastChess.c_y + i * dy * GRID_SIZE;

        bool found = false;
        for (const auto& chess : chesses) {
            if (chess.color == lastChess.color && chess.c_x == x && chess.c_y == y) {
                count++;
                found = true;
                break;
            }
        }
        if (!found) break;
    }

    // 检查反方向
    for (int i = 1; i < countNeeded; i++) {
        int x = lastChess.c_x - i * dx * GRID_SIZE;
        int y = lastChess.c_y - i * dy * GRID_SIZE;

        bool found = false;
        for (const auto& chess : chesses) {
            if (chess.color == lastChess.color && chess.c_x == x && chess.c_y == y) {
                count++;
                found = true;
                break;
            }
        }
        if (!found) break;
    }

    return count >= countNeeded;
}

// 检查三三禁手（黑棋不能同时形成两个活三）
bool gomuku_CheckDoubleThree(const std::vector<Chess>& chesses, const Chess& lastChess) {
    if (lastChess.color != BLACK) return false; // 只有黑棋有禁手

    int activeThrees = 0;

    // 检查四个方向（水平、垂直、主对角线、副对角线）
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int i = 0; i < 4; i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];

        // 检查是否形成活三（即可以发展成活四的三）
        if (gomuku_CheckDirection(chesses, lastChess, dx, dy, 3)) {
            // 检查两端是否为空（确保是活三）
            int x1 = lastChess.c_x + 3 * dx * GRID_SIZE;
            int y1 = lastChess.c_y + 3 * dy * GRID_SIZE;
            int x2 = lastChess.c_x - 3 * dx * GRID_SIZE;
            int y2 = lastChess.c_y - 3 * dy * GRID_SIZE;

            bool end1Empty = true;
            bool end2Empty = true;

            for (const auto& chess : chesses) {
                if (chess.c_x == x1 && chess.c_y == y1) end1Empty = false;
                if (chess.c_x == x2 && chess.c_y == y2) end2Empty = false;
            }

            if (end1Empty && end2Empty) {
                activeThrees++;
                if (activeThrees >= 2) return true; // 双活三，禁手
            }
        }
    }

    return false;
}

// 检查四四禁手（黑棋不能同时形成两个四）
bool gomuku_CheckDoubleFour(const std::vector<Chess>& chesses, const Chess& lastChess) {
    if (lastChess.color != BLACK) return false; // 只有黑棋有禁手

    int fours = 0;

    // 检查四个方向（水平、垂直、主对角线、副对角线）
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int i = 0; i < 4; i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];

        // 检查是否形成四（活四或冲四）
        if (gomuku_CheckDirection(chesses, lastChess, dx, dy, 4)) {
            fours++;
            if (fours >= 2) return true; // 双四，禁手
        }
    }

    return false;
}

// 检查黑棋是否触犯禁手
bool gomuku_CheckForbidden(const std::vector<Chess>& chesses, const Chess& lastChess) {
    if (lastChess.color != BLACK) return false; // 只有黑棋有禁手

    return gomuku_CheckDoubleThree(chesses, lastChess) || gomuku_CheckDoubleFour(chesses, lastChess);
}

// 检查是否获胜（修改后的版本，包含禁手判断）
int gomuku_CheckWin(const std::vector<Chess>& chesses, const Chess& lastChess) {
    if (lastChess.color == BLACK && gomuku_CheckForbidden(chesses, lastChess)) {
        return BLACK_FORBIDDEN; // 黑棋禁手
    }

    if (gomuku_CheckDirection(chesses, lastChess, 1, 0, 5) || // 水平
        gomuku_CheckDirection(chesses, lastChess, 0, 1, 5) || // 垂直
        gomuku_CheckDirection(chesses, lastChess, 1, 1, 5) || // 主对角线
        gomuku_CheckDirection(chesses, lastChess, 1, -1, 5)) { // 副对角线
        return (lastChess.color == BLACK) ? BLACK_WIN : WHITE_WIN;
        }

    return NORMAL_WIN; // 未分胜负
}