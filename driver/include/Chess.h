//
// Created by 冯于洋 on 25-5-16.
//

#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <vector>
#include "draw.h"
#define CHESSBLACK 100
#define CHESSWHITE 200
class Chess {
public:
    Chess(int gx, int gy, int color) :
        grid_x(gx), grid_y(gy),
        c_x(OFFSET_X + gx * GRID_SIZE),
        c_y(OFFSET_Y + gy * GRID_SIZE),
        color(color) {
        std::cout << "Chess(gx, gy, color) constructed at " << this << "\n";
    }
    int grid_x; // 网格坐标 (0-18)
    int grid_y; // 网格坐标 (0-18)
    float c_x;
    float c_y;
    int c_r = 18;
    int color;
    bool is_Chess_Exist(std::vector<Chess>& chesses);

};
bool get_Grid_Pos(int x, int y, int& grid_x, int& grid_y);
#endif //OPERATION_H