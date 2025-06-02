//
// Created by 冯于洋 on 25-5-16.
//
#include <easyx.h>

#include "Chess.h"

#include <cmath>

#include "draw.h"
#include "Go.h"
#include "Player.h"

extern std::vector<Chess>chesses;

bool get_Grid_Pos(int pixel_x, int pixel_y, int& grid_x, int& grid_y) {
    // 转换为相对于棋盘的坐标
    float rel_x = pixel_x - OFFSET_X;
    float rel_y = pixel_y - OFFSET_Y;

    // 检查是否在棋盘范围内
    if (rel_x < 0 || rel_x >= BOARD_WIDTH ||
        rel_y < 0 || rel_y >= BOARD_HEIGHT) {
        return false;
        }

    // 计算最近的网格点（四舍五入）
    grid_x = static_cast<int>(std::round(rel_x / GRID_SIZE));
    grid_y = static_cast<int>(std::round(rel_y / GRID_SIZE));

    // 确保在有效范围内
    return (grid_x >= 0 && grid_x < BOARD_GRID_SIZE &&
            grid_y >= 0 && grid_y < BOARD_GRID_SIZE);
}

bool Chess::is_Chess_Exist(std::vector<Chess>& chesses) {
    for (const auto& chess : chesses) {
        if (this -> c_x == chess.c_x && this -> c_y == chess.c_y) {
            return true;
        }
    }
    return false;
}


