#include "game.hpp"
#include "graphics.hpp"
#include <iostream>

Game::Game(int x, int y, int size, GameMaster *master, std::function<void()> on_pause, std::function<void(const std::string&)> on_game_over, bool bot_game)
    : Widget(x, y, size, size), master(master),
      pause_button(x + size + 20, y + 50, 100, 30, "Pause", on_pause),
      board_size(size / 20), time_left(5), is_paused(false), game_over_callback(on_game_over), is_bot_game(bot_game)
{
    reset();
}

void Game::draw() const
{

    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            genv::gout << genv::move_to(x + i * 20, y + j * 20) << genv::color(200, 200, 200) << genv::box(20, 20);
            genv::gout << genv::move_to(x + i * 20, y + j * 20) << genv::color(0, 0, 0) << genv::line(20, 0);
            genv::gout << genv::move_to(x + i * 20, y + j * 20) << genv::color(0, 0, 0) << genv::line(0, 20);
            if (board[i][j] == 1)
            {
                genv::gout << genv::move_to(x + i * 20 + 5, y + j * 20 + 15) << genv::color(0, 0, 0) << genv::text("X");
            }
            else if (board[i][j] == 2)
            {
                genv::gout << genv::move_to(x + i * 20 + 5, y + j * 20 + 15) << genv::color(0, 0, 0) << genv::text("O");
            }
        }
    }

    int info_x = x + board.size() * 20 + 40;

    genv::gout << genv::move_to(info_x, y + 20) << genv::color(255, 255, 255) << genv::text("Current player: " + std::string((master->get_current_player() == 1) ? "X" : "O"));
    pause_button.draw();
}

void Game::handle_event(const genv::event &ev)
{
    if (!is_paused && ev.type == genv::ev_mouse && ev.button == genv::btn_left)
    {
        int row = (ev.pos_x - x) / 20;
        int col = (ev.pos_y - y) / 20;
        if (row >= 0 && row < board.size() && col >= 0 && col < board.size() && board[row][col] == 0)
        {
            board[row][col] = master->get_current_player();
            master->make_move(row, col);
            if (master->check_win(row, col))
            {
                std::string winner = (master->get_current_player()==1) ? "X wins!" : "O wins!";
                winner = (master->get_current_player()==2) ? "O wins!" : "X wins!";

                game_over_callback(winner);

            }
            else if (is_bot_game && master->get_current_player() == 2)
            {
                bot_move();
            }

        }
    }
    pause_button.handle_event(ev);
}

void Game::reset()
{
    board = std::vector<std::vector<int>>(board_size, std::vector<int>(board_size, 0));
    time_left = 5;
}

void Game::update_timer()
{
    if (!is_paused)
    {
        --time_left;
        if (time_left == 0)
        {

        }
    }
}

void Game::pause()
{
    is_paused = true;
}

void Game::resume()
{
    is_paused = false;
}

void Game::bot_move()
{
    auto move = ai_player.calculate_move(board, master->get_current_player());
    int row = move.first;
    int col = move.second;
    if (row >= 0 && col >= 0)
    {
        board[row][col] = master->get_current_player();
        master->make_move(row, col);
        if (master->check_win(row, col))
        {
            std::string winner = (master->get_current_player() == 1) ? "X wins!" : "O wins!";
            game_over_callback(winner);
        }
    }
}
