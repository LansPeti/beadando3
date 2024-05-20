#include "pause_menu.hpp"
#include "graphics.hpp"

PauseMenu::PauseMenu(int x, int y, int width, int height, std::function<void()> on_resume, std::function<void()> on_restart, std::function<void()> on_menu)
    : Widget(x, y, width, height),
      resume_button(x + width / 2 - 50, y + height / 2 - 100, 100, 50, "Resume", on_resume),
      restart_button(x + width / 2 - 50, y + height / 2 - 0, 100, 50, "Restart", on_restart),
      menu_button(x + width / 2 - 50, y + height / 2 + 100, 100, 50, "Back to Menu", on_menu) {}

void PauseMenu::draw() const {
    genv::gout << genv::move_to(x, y) << genv::color(0, 0, 0) << genv::box(width, height);
    resume_button.draw();
    restart_button.draw();
    menu_button.draw();
}

void PauseMenu::handle_event(const genv::event &ev) {
    resume_button.handle_event(ev);
    restart_button.handle_event(ev);
    menu_button.handle_event(ev);
}
