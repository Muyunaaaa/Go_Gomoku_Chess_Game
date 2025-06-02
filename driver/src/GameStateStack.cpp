//
// Created by Administrator on 25-6-1.
//
#include "GameStateStack.h"

void GameStateStack::pushState(const std::string& state) {
    states.push(state);
}

std::string GameStateStack::popState() {
    if (!states.empty()) {
        std::string top = states.top();
        states.pop();
        return top;
    }
    return ""; // 空栈时返回空字符串
}

std::string GameStateStack::peekState() const {
    if (!states.empty()) {
        std::string result = states.top();
        return result;
    }
    return "";
}

bool GameStateStack::isEmpty() const {
    return states.empty();
}

void GameStateStack::clear() {
    while (!states.empty()) {
        states.pop();
    }
}