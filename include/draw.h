//
// Created by 冯于洋 on 25-5-16.
//

#ifndef BOARD_H
#define BOARD_H

#define GRID_N 18                          // 19条线 = 18个格子
#define GRID_SIZE 48                       // 自动调整为48像素格子大小
#define X_BOUND 1536
#define Y_BOUND 1024
#define BOARD_WIDTH (GRID_N * GRID_SIZE)  // = 864
#define BOARD_HEIGHT (GRID_N * GRID_SIZE) // = 864
#define OFFSET_X ((X_BOUND - BOARD_WIDTH) / 2) // = (1536 - 864) / 2 = 336
#define OFFSET_Y ((Y_BOUND - BOARD_HEIGHT) / 2) // = (1024 - 864) / 2 = 80


#include <vector>
class Chess;
void draw_Board();
void draw_Chess(std::vector<Chess>);
#endif //BOARD_H
