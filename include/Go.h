//
// Created by Administrator on 25-6-1.
//

#ifndef GO_H
#define GO_H

#include <vector>

const int GRID_DIRECTIONS[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}}; // 网格相邻方向
const int BOARD_GRID_SIZE = 19; // 19x19棋盘 (0-18)

class Chess;
    // 判断坐标是否在棋盘范围内
    bool isWithinBoard(int x, int y);

    // 获取连通气块与是否有气
    void getConnectedBlockAndLiberties(const std::vector<Chess>& chesses, const Chess& start,
                                       std::vector<Chess>& block, bool& hasLiberty);

    // 移除对方无气棋子
    void removeCapturedChesses(std::vector<Chess>& chesses, const Chess& lastChess);

    // 执行围棋规则（落子后检查提子）
    void execute_Go_Rules();

    // 判断围棋胜负（简化版）
    int go_CheckWin(const std::vector<Chess>& chesses, const Chess& lastChess);
#endif // GO_H
