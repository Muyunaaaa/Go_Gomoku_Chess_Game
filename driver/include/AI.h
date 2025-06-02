//
// Created by Administrator on 25-6-2.
//

#ifndef AI_H
#define AI_H
#include <vector>

class Chess;

class AI {
public:
    AI();

    ~AI();

    void get_Chess_Position(int &x, int &y); // 获取 AI 落子坐标
    bool put_Chess(); // 执行 AI 落子，绘制并检查胜负
};

// 五子棋评估函数
int evaluatePosition(int x, int y, int color); // 单点评分（进攻或防守）
void evaluateGomokuPosition(int &x, int &y); // 获取五子棋 AI 最佳落子点

// 围棋评估函数
void evaluateGoPosition(int &x, int &y); // 获取围棋 AI 最佳落子点
int evaluateGoMove(int x, int y); // 对围棋落子进行评分
bool hasLiberty(int x, int y, int color); // 检查当前位置是否有气
bool canCapture(int x, int y, int color); // 是否能吃子
bool isSuicidal(int x, int y, int color); // 判断是否是自杀落子

// 工具函数
bool isPositionEmpty(int x, int y); // 检查某位置是否为空
int distanceToNearestOpponent(int x, int y, int opponentColor); // 距离敌方棋子
#endif //AI_H
