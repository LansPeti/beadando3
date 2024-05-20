#include "pause_menu.hpp"
#include "graphics.hpp"

PauseMenu::PauseMenu(int x, int y, int width, int height, std::function<void()> on_resume, std::function<void()> on_restart, std::function<void()> on_menu)
    : Widget(x, y, width, height),
      resume_button(x + width / 2 - 100, y + height / 2 - 50, 200, 50, "Resume", on_resume),
      restart_button(x + width / 2 - 100, y + height / 2 +50, 200, 50, "Restart", on_restart),
      menu_button(x + width / 2 - 100, y + height / 2 + 150, 200, 50, "Back to Main Menu", on_menu),
      title("Tic Tac Toe"),
      title2("a Peter Lanszki production") {}

void PauseMenu::draw() const
{
    genv::gout << genv::move_to(x, y) << genv::color(0, 0, 0) << genv::box(width, height);
    genv::gout << genv::move_to(x + width / 2 - genv::gout.twidth(title) / 2, y + height / 4) << genv::color(255, 255, 255) << genv::text(title);
    genv::gout << genv::move_to(x + width / 2 - genv::gout.twidth(title2) / 2, y + height / 4 +50) << genv::color(255, 255, 255) << genv::text(title2);
    resume_button.draw();
    restart_button.draw();
    menu_button.draw();
}

void PauseMenu::handle_event(const genv::event &ev)
{
    resume_button.handle_event(ev);
    restart_button.handle_event(ev);
    menu_button.handle_event(ev);
}
