//
// Created by Administrator on 25-5-27.
//

#ifndef GOMOKU_H
#define GOMOKU_H
#include <vector>

class Chess;

int gomoku_CheckWin(const std::vector<Chess>& chesses, const Chess& lastChess);
bool gomoku_CheckDirection(const std::vector<Chess>& chesses, const Chess& lastChess, int dx, int dy);
bool gomoku_CheckForbidden(const std::vector<Chess>& chesses, const Chess& lastChess); // 检查黑棋禁手
bool gomoku_CheckDoubleThree(const std::vector<Chess>& chesses, const Chess& lastChess); // 检查三三禁手
bool gomoku_CheckDoubleFour(const std::vector<Chess>& chesses, const Chess& lastChess); // 检查四四禁手
#endif //GOMOKU_H
