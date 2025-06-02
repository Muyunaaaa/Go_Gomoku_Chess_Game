//
// Created by Administrator on 25-6-1.
//

#ifndef GAMESTACKSTATE_H
#define GAMESTACKSTATE_H
#include <stack>
#include <string>
#include <iomanip>
#include "GameStateStack.h"
class GameStateStack {
private:
    std::stack<std::string> states;

public:
    // 压入一个新状态
    void pushState(const std::string& state);

    // 弹出上一个状态（返回并删除）
    std::string popState();

    // 获取当前状态（不删除）
    std::string peekState() const;

    // 判断栈是否为空
    bool isEmpty() const;

    // 清空所有状态
    void clear();
};
#endif //GAMESTACKSTATE_H
