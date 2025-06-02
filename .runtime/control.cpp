//
// Created by 冯于洋 on 25-5-16.
#include "control.h"
#include "aim.h"
#include <Easyx/easyx.h>
#include "rule.h"
#include "game.h"
#include <Easyx/graphics.h>
int chesscolor = BLACK;
void Player::put_Chess() {
    Chess newchess(p_x, p_y, chesscolor);
    if (!newchess.is_Chess_Exist(chesses)) {
        chesses.push_back(newchess);

        int result = checkWin(chesses, newchess);
        if (result != NORMAL_WIN) {
            showGameOverDialog(result); // 传入不同的结果状态
            return;
        }

        // 切换玩家
        chesscolor = (chesscolor == BLACK) ? WHITE : BLACK;
    }
}

void Player::move(ExMessage msg) {
    if (msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {
            case VK_UP: {
                if (this -> p_y > GRID_SIZE) {
                    this->p_y -= GRID_SIZE;
                }
                break;
            }
            case VK_DOWN: {
                if (this -> p_y < Y_BOUND - GRID_SIZE) {
                    this->p_y += GRID_SIZE;
                }
                break;
            }
            case VK_LEFT: {
                if (this -> p_x > GRID_SIZE) {
                    this->p_x -= GRID_SIZE;
                }
                break;
            }
            case VK_RIGHT: {
                if (this -> p_x < X_BOUND - GRID_SIZE)
                this->p_x += GRID_SIZE;
                break;
            }
            case VK_SPACE: {
                this->put_Chess();
                break;
            }
        }
    }
}
Player::~Player() {
}

