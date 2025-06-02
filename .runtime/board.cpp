//
// Created by 冯于洋 on 25-5-16.
//
#include <easyx.h>
#include "board.h"
#define GRID_N 18
#define GRID_SIZE 30
#define OFFSET_X 30
#define OFFSET_Y 30
/*
void draw_Board() {
    IMAGE bk;
    loadimage(&bk,"image/board.jpg",X_BOUND,Y_BOUND);
    putimage(0,0,&bk);

    int line_x = 30,line_y = 30;
    for (int i = 0; i <= GRID_N;i++) {
        setlinecolor(BLACK);
        line(OFFSET_X,line_x,X_BOUND - OFFSET_X,line_x);
        line(line_y,OFFSET_Y,line_y,Y_BOUND - OFFSET_Y);
        line_x += GRID_SIZE;
        line_y += GRID_SIZE;
    }
    setfillcolor(BLACK);
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            fillcircle(OFFSET_X + (3+j*6) * GRID_SIZE,OFFSET_X + (3+i*6) * GRID_SIZE,4);
        }
    }
}*/