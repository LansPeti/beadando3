#include "pause_menu.hpp"
#include "graphics.hpp"

PauseMenu::PauseMenu(int x, int y, int width, int height, std::function<void()> on_resume)
    : Widget(x, y, width, height),
      resume_button(x + width / 2 - 50, y + height / 2 - 25, 100, 50, "Resume", on_resume) {}

void PauseMenu::draw() const {
    genv::gout << genv::move_to(x, y) << genv::color(0, 0, 0) << genv::box(width, height);
    resume_button.draw();
}

void PauseMenu::handle_event(const genv::event &ev) {
    resume_button.handle_event(ev);
}
