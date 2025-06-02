#include "ai.h"
#include "chess.h"
#include "draw.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>
#include <windows.h>

#include "easyx.h"
#include "game.h"
#include "GameStateStack.h"
#include "Go.h"
#include "Gomoku.h"

extern GameStateStack _stack;
extern std::vector<Chess> chesses;
extern int chesscolor;

// 方向数组：上、右、右上、右下
const int dx[] = {0, 1, 1, 1};
const int dy[] = {1, 0, 1, -1};

// 判断位置是否为空
bool isPositionEmpty(int x, int y) {
    for (const auto& c : chesses) {
        if (c.c_x == x && c.c_y == y) return false;
    }
    return true;
}

// 获取棋盘上的棋子颜色
int getColorAt(int x, int y) {
    for (const auto& c : chesses) {
        if (c.c_x == x && c.c_y == y) return c.color;
    }
    return 0;
}

// ----------- GOMOKU（五子棋）逻辑 -----------

int evaluatePosition(int x, int y, int color) {
    int score = 0;
    for (int dir = 0; dir < 4; ++dir) {
        int count = 1;
        int blocks = 0;

        // 正方向
        for (int i = 1; i <= 4; ++i) {
            int nx = x + dx[dir] * i;
            int ny = y + dy[dir] * i;
            if (nx < 0 || ny < 0 || nx >= GRID_N || ny >= GRID_N) {
                blocks++;
                break;
            }
            int c = getColorAt(nx, ny);
            if (c == color) count++;
            else if (c == 0) break;
            else {
                blocks++;
                break;
            }
        }

        // 反方向
        for (int i = 1; i <= 4; ++i) {
            int nx = x - dx[dir] * i;
            int ny = y - dy[dir] * i;
            if (nx < 0 || ny < 0 || nx >= GRID_N || ny >= GRID_N) {
                blocks++;
                break;
            }
            int c = getColorAt(nx, ny);
            if (c == color) count++;
            else if (c == 0) break;
            else {
                blocks++;
                break;
            }
        }

        // 评分规则
        if (count >= 5) score += 100000;
        else if (count == 4 && blocks == 0) score += 10000;
        else if (count == 4 && blocks == 1) score += 1000;
        else if (count == 3 && blocks == 0) score += 500;
        else if (count == 3 && blocks == 1) score += 100;
        else if (count == 2 && blocks == 0) score += 50;
    }
    return score;
}

void evaluateGomokuPosition(int& x, int& y) {
    if (chesses.empty()) {
        x = y = GRID_N / 2;
        return;
    }

    int bestScore = -1;
    std::vector<std::pair<int, int>> candidates;

    for (int i = 0; i < GRID_N; ++i) {
        for (int j = 0; j < GRID_N; ++j) {
            if (!isPositionEmpty(i, j)) continue;

            int myScore = evaluatePosition(i, j, chesscolor);
            int oppScore = evaluatePosition(i, j, (chesscolor == BLACK) ? WHITE : BLACK);

            int totalScore = myScore + oppScore * 0.8;

            if (totalScore > bestScore) {
                bestScore = totalScore;
                candidates.clear();
                candidates.emplace_back(i, j);
            } else if (totalScore == bestScore) {
                candidates.emplace_back(i, j);
            }
        }
    }

    if (!candidates.empty()) {
        int index = rand() % candidates.size();
        x = candidates[index].first;
        y = candidates[index].second;
    } else {
        x = y = GRID_N / 2;
    }
}

// ----------- GO（围棋）逻辑 -----------

bool hasLiberty(int x, int y) {
    const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for (int i = 0; i < 4; ++i) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx >= 0 && ny >= 0 && nx < GRID_N && ny < GRID_N && isPositionEmpty(nx, ny))
            return true;
    }
    return false;
}

bool isSuicidal(int x, int y, int color) {
    chesses.push_back(Chess(x, y, color));
    bool result = !hasLiberty(x, y);
    chesses.pop_back();
    return result;
}

int distanceToNearestOpponent(int x, int y, int oppColor) {
    int minDist = INT_MAX;
    for (const auto& c : chesses) {
        if (c.color == oppColor) {
            int d = abs(c.c_x - x) + abs(c.c_y - y);
            minDist = std::min(minDist, d);
        }
    }
    return minDist == INT_MAX ? 0 : minDist;
}

int evaluateGoMove(int x, int y) {
    int score = 0;
    int oppColor = (chesscolor == BLACK) ? WHITE : BLACK;

    score += 100 - distanceToNearestOpponent(x, y, oppColor);
    if (hasLiberty(x, y)) score += 50;
    if (isSuicidal(x, y, chesscolor)) score -= 100;

    return score;
}

void evaluateGoPosition(int& x, int& y) {
    if (chesses.empty()) {
        const int star[3] = {3, 9, 15};
        x = star[rand() % 3];
        y = star[rand() % 3];
        return;
    }

    struct Move { int x, y, score; };
    std::vector<Move> candidates;

    for (int i = 0; i < GRID_N; ++i) {
        for (int j = 0; j < GRID_N; ++j) {
            if (!isPositionEmpty(i, j)) continue;
            int s = evaluateGoMove(i, j);
            candidates.push_back({i, j, s});
        }
    }

    std::sort(candidates.begin(), candidates.end(), [](const Move& a, const Move& b) {
        return a.score > b.score;
    });

    if (!candidates.empty()) {
        int topN = std::min((int)candidates.size(), 5);
        int idx = rand() % topN;
        x = candidates[idx].x;
        y = candidates[idx].y;
    } else {
        x = y = GRID_N / 2;
    }
}

// ----------- AI 类函数实现 -----------

AI::AI() { srand((unsigned)time(nullptr)); }

AI::~AI() {}

void AI::get_Chess_Position(int& x, int& y) {
    if (_stack.peekState() == "GOMOKU") {
        evaluateGomokuPosition(x, y);
    } else if (_stack.peekState() == "GO") {
        evaluateGoPosition(x, y);
    }
}

bool AI::put_Chess() {
    int gx, gy;
    get_Chess_Position(gx, gy);
    Chess newChess(gx, gy, chesscolor);
    if (!newChess.is_Chess_Exist(chesses)) {
        chesses.push_back(newChess);
        Sleep(300);

        BeginBatchDraw();
        cleardevice();
        draw_Board();
        draw_Chess(chesses);
        EndBatchDraw();

        int result = (_stack.peekState() == "GOMOKU")
                     ? gomoku_CheckWin(chesses, newChess)
                     : go_CheckWin(chesses, newChess);

        chesscolor = (chesscolor == BLACK) ? WHITE : BLACK;

        return result != NORMAL_WIN;
    }
    return NORMAL_WIN;
}