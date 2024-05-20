#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include "widget.hpp"
#include "button.hpp"

class PauseMenu : public Widget {
    Button resume_button;
public:
    PauseMenu(int x, int y, int width, int height, std::function<void()> on_resume);
    void draw() const override;
    void handle_event(const genv::event &ev) override;
};

#endif
