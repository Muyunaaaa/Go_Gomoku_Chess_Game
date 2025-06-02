//
// Created by Administrator on 25-6-1.
//

#ifndef UI_H
#define UI_H
#include <string>
#include <vector>
#include <easyx.h>
#include <iomanip>

namespace UI {
    typedef struct button {
        int x_left;
        int y_top;
        int y_bottom;
        int x_right;
        std::string message;
    } Button;

    class UI {
    public:
        UI();

        virtual void add_Button(int p_x_left,int p_x_right,int p_y_top,int p_y_bottom,std::string messeage);//根据图片中我指定的四个边界的部分，为创建的ui这个对象获取一个对应的button结构体，这个参数由我来手动设置

        virtual bool setup();//将图片显示出来，并设置好按钮位置

        virtual std::string recall();//等待用户的操作，如果点击到了任何一个按钮的范围，则返回对应按钮的信息

        virtual void endup();//清除图片绘制，进行下一步操作
    };

    class Init_UI : public UI {
    private:
        std::vector<Button> buttons;
        std::string type;
        IMAGE image;
        std::string result;

    public:
        Init_UI();

        virtual void add_Button(int p_x_left,int p_x_right,int p_y_top,int p_y_bottom,std::string messeage);

        virtual bool setup();

        virtual std::string recall();

        virtual void endup();
    };

    class Select_Mode_UI : public UI {
    private:
        std::vector<Button> buttons;
        std::string type;
        IMAGE image;
        std::string result;

    public:
        Select_Mode_UI();

        virtual void add_Button(int p_x_left,int p_x_right,int p_y_top,int p_y_bottom,std::string messeage);

        virtual bool setup();

        virtual std::string recall();

        virtual void endup();
    };

    class Select_Game_UI : public UI {
    private:
        std::vector<Button> buttons;
        std::string type;
        IMAGE image;
        std::string result;

    public:
        Select_Game_UI();

        virtual void add_Button(int p_x_left,int p_x_right,int p_y_top,int p_y_bottom,std::string messeage);

        virtual bool setup();

        virtual std::string recall();

        virtual void endup();
    };

    class Select_Show_UI : public UI {
    private:
        std::vector<Button> buttons;
        std::string type;
        IMAGE image;
        std::string result;

    public:
        Select_Show_UI();

        virtual void add_Button(int p_x_left,int p_x_right,int p_y_top,int p_y_bottom,std::string messeage);

        virtual bool setup();

        virtual std::string recall();

        virtual void endup();
    };
}
#endif //UI_H
