#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "widget.hpp"
#include "button.hpp"
#include <vector>
#include <functional>

class MainMenu : public Widget {
    std::string title;
    Button button1;
    Button button2;
    Button size_button;
    int board_size;
public:
    MainMenu(int x, int y, int width, int height, std::function<void()> on_pvp, std::function<void()> on_bot);
    void draw() const override;
    void handle_event(const genv::event &ev) override;
    int get_board_size() const;
};

#endif
