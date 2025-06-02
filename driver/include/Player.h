//
// Created by 冯于洋 on 25-5-16.
//

#ifndef LOGIC_H
#define LOGIC_H
#define BLACK_PLAYER 114
#define WHITE_PLAYER 115
#define HUMAN_MACHINE 116
#define HUMAN_PLAYER 117
#include <string>
#include <iostream>

#include "graphics.h"

class Player {
private:
public:
    Player();
    Player(std::string _UUID,int type) : type(type), UUID(_UUID){}
    int points = 0;
    std::string UUID;
    int type;//玩家和机器人两种类型
    bool two_player_put_Chess(MOUSEMSG m);
    bool computer_and_player_put_Chess(MOUSEMSG m);
    ~Player();
    //内存问题未解决
};
#endif //LOGIC_H
