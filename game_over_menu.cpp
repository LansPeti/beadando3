#include "game_over_menu.hpp"
#include "graphics.hpp"

GameOverMenu::GameOverMenu(int x, int y, int width, int height, std::string winner, std::function<void()> on_restart, std::function<void()> on_menu)
    : Widget(x, y, width, height), winner(winner),
      restart_button(x + width / 2 - 100, y + height / 2 - 0, 200, 50, "Restart", on_restart),
      menu_button(x + width / 2 - 100, y + height / 2 + 100, 200, 50, "Back to Main Menu", on_menu) {}

void GameOverMenu::draw() const
{
    genv::gout << genv::move_to(x, y) << genv::color(0, 0, 0) << genv::box(width, height);
    genv::gout << genv::move_to(x + width / 2 - genv::gout.twidth(winner) / 2, y + height / 2 - 75) << genv::color(255, 255, 255) << genv::text(winner);
    restart_button.draw();
    menu_button.draw();
}

void GameOverMenu::handle_event(const genv::event &ev)
{
    restart_button.handle_event(ev);
    menu_button.handle_event(ev);
}
