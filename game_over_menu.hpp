#ifndef GAME_OVER_MENU_HPP
#define GAME_OVER_MENU_HPP

#include "widget.hpp"
#include "button.hpp"

class GameOverMenu : public Widget {
    std::string winner;
    Button restart_button;
    Button menu_button;
public:
    GameOverMenu(int x, int y, int width, int height, std::string winner, std::function<void()> on_restart, std::function<void()> on_menu);
    void draw() const override;
    void handle_event(const genv::event &ev) override;
};

#endif
