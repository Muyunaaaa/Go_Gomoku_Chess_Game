//
// Created by 冯于洋 on 25-5-16.
#include "Player.h"

#include <iostream>
#include <easyx.h>
#include <memory>
#include <math.h>
#include <conio.h>
#include <iomanip>
#include <string>
#include <vector>

#include "Chess.h"
#include "draw.h"
#include "game.h"
#include "GameStateStack.h"
#include "Go.h"
#include "Gomoku.h"
#include "graphics.h"

std::vector<Chess>chesses;
std::vector<std::vector<Chess>>chessesBuff;
extern GameStateStack _stack;
int chesscolor = BLACK;

bool Player::put_Chess() {
    MOUSEMSG m = GetMouseMsg();
    if (m.uMsg == WM_LBUTTONDOWN) {
        if (peek_DrawBack(m)) {
            if (!chessesBuff.empty()&&chessesBuff.size()>1) {
                chessesBuff.pop_back();
                chesses = chessesBuff.back();
                chesscolor = (chesscolor == BLACK) ? WHITE : BLACK;
                BeginBatchDraw();
                cleardevice();
                draw_Board();
                draw_Chess(chesses);
                EndBatchDraw();
            }
        }
        else if (peek_Restart(m)) {
            chesses.clear();
            chessesBuff.clear();
            BeginBatchDraw();
            cleardevice();
            draw_Board();
            draw_Chess(chesses);
            EndBatchDraw();
            chesscolor = BLACK;
        }
        else if (peek_Concede(m)) {
            cleardevice();
            chesscolor = (chesscolor == BLACK) ? WHITE : BLACK;
            return true;
        }
        else {
            int gx, gy;
            std::cout<<"gx:"<<gx<<"gy:"<<gy<<std::endl;
            if (get_Grid_Pos(m.x, m.y, gx, gy)) {
                std::cout<<"gx:"<<gx<<"gy:"<<gy<<std::endl;
                Chess newchess(static_cast<int>(gx), static_cast<int>(gy), chesscolor);
                if (!newchess.is_Chess_Exist(chesses)) {
                    chesses.push_back(newchess);
                    if (_stack.peekState() == "GOMOKU") {
                        BeginBatchDraw();
                        int result = gomoku_CheckWin(chesses, newchess);
                        cleardevice();
                        draw_Board();
                        draw_Chess(chesses);
                        EndBatchDraw();
                        if (result != NORMAL_WIN) {
                            return true; // 游戏结束，胜负已分
                        }
                    }
                    else if (_stack.peekState() == "GO") {
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
                    // 切换玩家
                    chesscolor = (chesscolor == BLACK) ? WHITE : BLACK;
                    chessesBuff.push_back(chesses);
                }
            }
        }
    }
    return false;
}

Player::~Player() {
}

