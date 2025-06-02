#include <iostream>
#include <easyx.h>
#include <memory>
#include <cstdlib>
#include <math.h>
#include <conio.h>
#include <iomanip>
#include "draw.h"
#include "Chess.h"
#include "game.h"
#include "Gomoku.h"
#include "Go.h"
#include <string>

#include "AI.h"
#include "UI.h"
#include "Player.h"
#include "GameStateStack.h"

extern GameStateStack _stack;
extern std::vector<Chess> chesses;
extern int chesscolor;
extern std::vector<std::vector<Chess>>chessesBuff;
UI::UI *init_ui = new UI::Init_UI();
UI::UI *select_game_ui = new UI::Select_Game_UI();
UI::UI *select_mode_ui = new UI::Select_Mode_UI();
UI::UI *select_show_ui = new UI::Select_Show_UI();

void game_Init() {
    init_ui->add_Button(317, 691, 746, 983, "START");
    init_ui->add_Button(840, 1216, 746, 983, "EXIT");

    select_game_ui->add_Button(240, 677, 417, 821, "GOMOKU");
    select_game_ui->add_Button(884, 1320, 417, 821, "GO");
    select_game_ui->add_Button(20, 90, 20, 73, "RETURN");

    select_mode_ui->add_Button(150, 522, 750, 986, "COMPUTER");
    select_mode_ui->add_Button(593, 983, 750, 986, "2 PLAYERS");
    select_mode_ui->add_Button(1054, 1428, 750, 986, "ONLINE");
    select_mode_ui->add_Button(20, 90, 20, 73, "RETURN");

    select_show_ui->add_Button(20, 90, 20, 73, "RETURN");
}
void game_Loop() {
    game_Init();
    while (true) {
        std::string state = _stack.peekState();
        if (state == "EXIT") {
            break;
        } else if (_stack.isEmpty()) {
            init_ui->setup();
        } else if (state == "START") {
            init_ui->endup();
            select_game_ui->setup();
        } else if (state == "RETURN") {
            _stack.popState();
            _stack.popState();
        } else if (state == "GOMOKU" || state == "GO") {
            select_game_ui->endup();
            select_mode_ui->setup();
        } else if (state == "ONLINE") {
            select_mode_ui->endup();
            online_Start();
            select_show_ui->setup();
        } else if (state == "2 PLAYERS") {
            select_mode_ui->endup();
            two_Player_Start();
            cleardevice();
            chesses.clear();
            chessesBuff.clear();
            select_show_ui->setup();
        } else if (state == "COMPUTER") {
            select_mode_ui->endup();
            computer_Start();
            cleardevice();
            chesses.clear();
            chessesBuff.clear();
            select_show_ui->setup();
        }
    }
    delete init_ui, select_game_ui, select_mode_ui;
    exit(0);
}

void two_Player_Start() {
    draw_Board();
    _stack.popState();
    Player players[2] = {Player("1111",HUMAN_PLAYER), Player("2222",HUMAN_PLAYER)};
    chesscolor = BLACK;
    while (1) {
        for (Player player: players) {
            MOUSEMSG m = GetMouseMsg();
            bool flag = player.two_player_put_Chess(m);
            if (flag) return;
        }
    }
}

void computer_Start() {
    draw_Board();
    _stack.popState();
    chesscolor = BLACK;

    Player player("Player1", HUMAN_PLAYER);
    AI ai;

    chesses.clear();
    chessesBuff.clear();

    while (true) {
        MOUSEMSG m = GetMouseMsg();

        if (m.uMsg == WM_LBUTTONDOWN) {
            // 撤回判断
            if (peek_DrawBack(m)) {
                if (chessesBuff.size() >= 2) {
                    chessesBuff.pop_back(); // AI 撤销
                    chessesBuff.pop_back(); // 玩家撤销
                    chesses = chessesBuff.empty() ? std::vector<Chess>() : chessesBuff.back();
                    chesscolor = BLACK;
                    BeginBatchDraw();
                    cleardevice();
                    draw_Board();
                    draw_Chess(chesses);
                    EndBatchDraw();
                }
                continue; // 跳过后续下棋逻辑
            }

            // 玩家下棋
            if (player.computer_and_player_put_Chess(m)) break;
            chessesBuff.push_back(chesses); // 保存玩家下完的状态

            // AI 下棋
            if (ai.put_Chess()) break;
            chessesBuff.push_back(chesses); // 保存 AI 下完的状态
        }
    }
}

void online_Start() {
    //完成双人在线对战，这里是很难的一部分，我需要达到两个人打开这个程序之后可以一起玩，这里涉及到很多网络知识
}

bool peek_DrawBack(MOUSEMSG m) {
    UI::button button_draw_back = {1313, 661, 827, 1488};
    if (m.x >= button_draw_back.x_left && m.x <= button_draw_back.x_right && m.y >= button_draw_back.y_top &&
        m.y <= button_draw_back.y_bottom) { return true; }
    return false;
}

bool peek_Concede(MOUSEMSG m) {
    UI::button button_concede = {1313, 416, 580, 1488};
    if (m.x >= button_concede.x_left && m.x <= button_concede.x_right && m.y >= button_concede.y_top &&
        m.y <= button_concede.y_bottom) { return true; }
    return false;
}

bool peek_Restart(MOUSEMSG m) {
    UI::button button_restart = {1313, 173, 337, 1488};
    if (m.x >= button_restart.x_left && m.x <= button_restart.x_right && m.y >= button_restart.y_top &&
        m.y <= button_restart.y_bottom) { return true; }
    return false;
}
