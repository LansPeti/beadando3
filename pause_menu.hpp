#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include "widget.hpp"
#include "button.hpp"
#include <functional>

class PauseMenu : public Widget
{
    std::string title;
    std::string title2;
    Button resume_button;
    Button restart_button;
    Button menu_button;
public:
    PauseMenu(int x, int y, int width, int height, std::function<void()> on_resume, std::function<void()> on_restart, std::function<void()> on_menu);
    void draw() const override;
    void handle_event(const genv::event &ev) override;
};

#endif
