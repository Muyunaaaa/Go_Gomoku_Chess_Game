//
// Created by Administrator on 25-5-26.
//
#include <iostream>
#include <easyx.h>
#include <memory>
#include <math.h>
#include <conio.h>
#include <iomanip>
#include "draw.h"
#include "game.h"
#include "Gomoku.h"
#include <string>
#include "GameStateStack.h"
#include "Chess.h"
#include "Go.h"


#include <graphics.h>
#include <windows.h>

#include <tchar.h>
#include <algorithm>

#include <graphics.h>
#include <windows.h>
#include <algorithm>  // for std::min
#include <conio.h>    // for _kbhit

int main() {
    // 强制关闭 DPI 缩放（防止被系统放大拉伸）
    SetProcessDPIAware();

    // 获取系统工作区大小（不包括任务栏）
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    int screenW = workArea.right - workArea.left;
    int screenH = workArea.bottom - workArea.top;

    // 原始设计分辨率
    int designW = 1536, designH = 1024;

    // 若屏幕装不下就按比例缩放
    float scale = std::min((float)screenW / designW, (float)screenH / designH);
    int winW = (int)(designW * scale);
    int winH = (int)(designH * scale);

    // 初始化图形窗口
    initgraph(winW, winH);

    // 获取窗口句柄
    HWND hwnd = GetHWnd();

    // 修改窗口样式，允许拉伸、最大化
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                 SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    // 窗口居中
    MoveWindow(hwnd,
               (screenW - winW) / 2,
               (screenH - winH) / 2,
               winW, winH,
               TRUE);

    while (!_kbhit()) {
        // 游戏逻辑
        game_Loop();
    }

    closegraph();
    return 0;
}