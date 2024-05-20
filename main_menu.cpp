#include "main_menu.hpp"
#include "graphics.hpp"

MainMenu::MainMenu(int x, int y, int width, int height, std::function<void()> on_pvp, std::function<void()> on_bot)
    : Widget(x, y, width, height),
      title("Tic Tac Toe"),
      title2("Made By Peter Lanszki"),
      button1(x + width / 4, y + height / 2 - 50, 150, 50, "Player vs Player", on_pvp),
      button2(x + 3 * width / 4 - 150, y + height / 2 - 50, 150, 50, "Player vs Bot", on_bot),
      size_button(x + width / 2 - 75, y + height / 2 + 50, 150, 50, "Board Size: 15x15", [this]()
{
    if (board_size == 15)
    {
        board_size = 30;
        size_button.set_label("Board Size: 30x30");
    }
    else
    {
        board_size = 15;
        size_button.set_label("Board Size: 15x15");
    }
}),
board_size(15) {}

void MainMenu::draw() const
{
    genv::gout << genv::move_to(x, y) << genv::color(0, 0, 0) << genv::box(width, height);
    genv::gout << genv::move_to(x + width / 2 - genv::gout.twidth(title) / 2, y + height / 4) << genv::color(255, 255, 255) << genv::text(title);
    genv::gout << genv::move_to(x + width / 2 - genv::gout.twidth(title2) / 2, y + height / 4 +50) << genv::color(255, 255, 255) << genv::text(title2);

    button1.draw();
    button2.draw();
    size_button.draw();
}

void MainMenu::handle_event(const genv::event &ev)
{
    button1.handle_event(ev);
    button2.handle_event(ev);
    size_button.handle_event(ev);
}

int MainMenu::get_board_size() const
{
    return board_size;
}
