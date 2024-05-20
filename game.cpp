#include "game.hpp"
#include "graphics.hpp"

Game::Game(int x, int y, int size, GameMaster *master, std::function<void()> on_pause, std::function<void(const std::string&)> on_game_over)
    : Widget(x, y, size, size), master(master),
      pause_button(x + size + 40, y + 50, 100, 30, "Pause", on_pause),
      board_size(size / 20), time_left(5), is_paused(false), game_over_callback(on_game_over) {
    reset();
}

void Game::draw() const {

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            genv::gout << genv::move_to(x + i * 20, y + j * 20) << genv::color(200, 200, 200) << genv::box(20, 20);
            genv::gout << genv::move_to(x + i * 20, y + j * 20) << genv::color(0, 0, 0) << genv::line(20, 0);
            genv::gout << genv::move_to(x + i * 20, y + j * 20) << genv::color(0, 0, 0) << genv::line(0, 20);
            if (board[i][j] == 1) {
                genv::gout << genv::move_to(x + i * 20 + 5, y + j * 20 + 15) << genv::color(0, 0, 0) << genv::text("X");
            } else if (board[i][j] == 2) {
                genv::gout << genv::move_to(x + i * 20 + 5, y + j * 20 + 15) << genv::color(0, 0, 0) << genv::text("O");
            }
        }
    }

    int info_x = x + board.size() * 20 + 40;
    genv::gout << genv::move_to(info_x, y + 20) << genv::color(255, 255, 255) << genv::text("Time left: " + std::to_string(time_left));
    genv::gout << genv::move_to(info_x, y + 100) << genv::color(255, 255, 255) << genv::text("Current player: " + std::string((master->get_current_player() == 1) ? "O" : "X"));
    pause_button.draw();
}

void Game::handle_event(const genv::event &ev) {
    if (!is_paused && ev.type == genv::ev_mouse && ev.button == genv::btn_left) {
        int row = (ev.pos_x - x) / 20;
        int col = (ev.pos_y - y) / 20;
        if (row >= 0 && row < board.size() && col >= 0 && col < board.size() && board[row][col] == 0) {
            master->make_move(row, col);
            board[row][col] = master->get_current_player();
            if (master->check_win(row, col)) {
                std::string winner = (master->get_current_player() == 1) ? "O wins!" : "X wins!";
                game_over_callback(winner);
            }
        }
    }
    pause_button.handle_event(ev);
}

void Game::reset() {
    board = std::vector<std::vector<int>>(board_size, std::vector<int>(board_size, 0));
    time_left = 5;
}

void Game::update_timer() {
    if (!is_paused) {
        --time_left;
        if (time_left == 0) {
            // később itt valahogy esetleg 5 másodperces stoppert rakok majd
        }
    }
}

void Game::pause() {
    is_paused = true;
}

void Game::resume() {
    is_paused = false;
}
