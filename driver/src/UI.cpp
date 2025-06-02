//
// Created by Administrator on 25-6-1.
//
#include "UI.h"
#include <graphics.h> // EasyX 头文件
#include <iostream>

#include "Chess.h"
#include "draw.h"
#include "GameStateStack.h"
using namespace std;
GameStateStack _stack;
extern int chesscolor;

namespace UI {

    // ========== UI 基类 ==========
    UI::UI() {}

    void UI::add_Button(int p_x_left, int p_x_right, int p_y_top, int p_y_bottom, std::string message) {
        // 空实现，留给派生类覆盖
    }

    bool UI::setup() {
        return false;
    }

    std::string UI::recall() {
        return "";
    }

    void UI::endup() {
    }

    // ========== Init_UI ==========
    Init_UI::Init_UI() {
        type = "Init";
    }

    void Init_UI::add_Button(int p_x_left, int p_x_right, int p_y_top, int p_y_bottom, std::string message) {
        Button btn = {p_x_left, p_y_top, p_y_bottom, p_x_right, message};
        buttons.push_back(btn);
    }

    bool Init_UI::setup() {
        initgraph(X_BOUND, Y_BOUND);
        loadimage(&image, "image/init_1.png"); // 加载背景图（文件需存在）
        putimage(0, 0, &image);
        result  = recall();
        _stack.pushState(result);
        return true;
    }

    std::string Init_UI::recall() {
        MOUSEMSG m;
        while (true) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                for (const auto& btn : buttons) {
                    if (m.x >= btn.x_left && m.x <= btn.x_right &&
                        m.y >= btn.y_top && m.y <= btn.y_bottom) {
                        return btn.message;
                    }
                }
            }
        }
    }

    void Init_UI::endup() {
        cleardevice();
    }

    // ========== Select_Mode_UI ==========
    Select_Mode_UI::Select_Mode_UI() {
        type = "Mode";
    }

    void Select_Mode_UI::add_Button(int p_x_left, int p_x_right, int p_y_top, int p_y_bottom, std::string message) {
        Button btn = {p_x_left, p_y_top, p_y_bottom, p_x_right, message};
        buttons.push_back(btn);
    }

    bool Select_Mode_UI::setup() {
        loadimage(&image, "image/init_3.png"); // 加载背景图（文件需存在）
        putimage(0, 0, &image);
        result  = recall();
        _stack.pushState(result);
        return true;
    }

    std::string Select_Mode_UI::recall() {
        MOUSEMSG m;
        while (true) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                for (const auto& btn : buttons) {
                    if (m.x >= btn.x_left && m.x <= btn.x_right &&
                        m.y >= btn.y_top && m.y <= btn.y_bottom) {
                        return btn.message;
                    }
                }
            }
        }
    }

    void Select_Mode_UI::endup() {
        cleardevice();
    }

    // ========== Select_Game_UI ==========
    Select_Game_UI::Select_Game_UI() {
        type = "Game";
    }

    void Select_Game_UI::add_Button(int p_x_left, int p_x_right, int p_y_top, int p_y_bottom, std::string message) {
        Button btn = {p_x_left, p_y_top, p_y_bottom, p_x_right, message};
        buttons.push_back(btn);
    }

    bool Select_Game_UI::setup() {
        loadimage(&image, "image/init_2.png"); // 加载背景图（文件需存在）
        putimage(0, 0, &image);
        result  = recall();
        _stack.pushState(result);
        return true;
    }

    std::string Select_Game_UI::recall() {
        MOUSEMSG m;
        while (true) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                for (const auto& btn : buttons) {
                    if (m.x >= btn.x_left && m.x <= btn.x_right &&
                        m.y >= btn.y_top && m.y <= btn.y_bottom) {
                        return btn.message;
                    }
                }
            }
        }
    }

    void Select_Game_UI::endup() {
        cleardevice();
    }

    Select_Show_UI::Select_Show_UI() {
        type = "Show";
    }

    void Select_Show_UI::add_Button(int p_x_left, int p_x_right, int p_y_top, int p_y_bottom, std::string message) {
        Button btn = {p_x_left, p_y_top, p_y_bottom, p_x_right, message};
        buttons.push_back(btn);
    }

    bool Select_Show_UI::setup() {
        if (chesscolor == WHITE) {
            loadimage(&image, "image/whitewin_return.png");
        }
        if (chesscolor == BLACK) {
            loadimage(&image, "image/blackwin_return.png");
        }
        putimage(0, 0, &image);
        result  = recall();
        _stack.pushState(result);
        return true;
    }

    std::string Select_Show_UI::recall() {
        MOUSEMSG m;
        while (true) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                for (const auto& btn : buttons) {
                    if (m.x >= btn.x_left && m.x <= btn.x_right &&
                        m.y >= btn.y_top && m.y <= btn.y_bottom) {
                        return btn.message;
                        }
                }
            }
        }
    }

    void Select_Show_UI::endup() {
        cleardevice();
    }
}