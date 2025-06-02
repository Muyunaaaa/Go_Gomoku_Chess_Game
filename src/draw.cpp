//
// Created by 冯于洋 on 25-5-16.
//
#include <easyx.h>
#include "draw.h"

#include "Chess.h"
#include "Player.h"

extern std::vector<Chess> chesses;
extern int chesscolor;
void draw_Board() {
    IMAGE bk;
    if (!chesses.empty() && chesscolor == BLACK) {
        loadimage(&bk, "image/White_round.png", X_BOUND, Y_BOUND);
        putimage(0, 0, &bk);
    }
    else {
        loadimage(&bk, "image/Black_round.png", X_BOUND, Y_BOUND);
        putimage(0, 0, &bk);
    }

    // 绘制棋盘线
    setlinecolor(RGB(122,81,29));
    setlinestyle(0,5);
    for (int i = 0; i <= GRID_N; i++) {
        int x = OFFSET_X + i * GRID_SIZE;
        int y = OFFSET_Y + i * GRID_SIZE;
        // 横线
        line(OFFSET_X, y, OFFSET_X + GRID_N * GRID_SIZE, y);
        // 竖线
        line(x, OFFSET_Y, x, OFFSET_Y + GRID_N * GRID_SIZE);
    }

    // 绘制星位（围棋的9个星）
    setfillcolor(RGB(109,73,37));
    int starPos[3] = {3, 9, 15}; // 在第4、10、16行列（0起计）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = OFFSET_X + starPos[j] * GRID_SIZE;
            int y = OFFSET_Y + starPos[i] * GRID_SIZE;
            fillcircle(x, y, 7);
        }
    }
}

void draw_Chess(std::vector<Chess> chesses) {
    for (const auto& newchess : chesses) {
        setlinestyle(PS_NULL, 1);
        setfillcolor(newchess.color);
        fillcircle(newchess.c_x,newchess.c_y,newchess.c_r);
    }
}
