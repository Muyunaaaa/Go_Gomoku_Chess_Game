//
// Created by Administrator on 25-5-17.
//

#ifndef GAME_H
#define GAME_H
#define BLACK_PLAYER 114
#define WHITE_PLAYER 115
#define HUMAN_MACHINE 116
#define HUMAN_PLAYER 117
#define NORMAL_WIN 0
#define BLACK_WIN 1
#define WHITE_WIN 2
#define BLACK_FORBIDDEN 3
#include <graphics.h>

bool is_Game_Over();
void game_Init();
void game_Loop();
void online_Start();
void two_Player_Start();
void computer_Start();
bool peek_DrawBack(MOUSEMSG m);
bool peek_Concede(MOUSEMSG m);
bool peek_Restart(MOUSEMSG m);
#endif //GAME_H