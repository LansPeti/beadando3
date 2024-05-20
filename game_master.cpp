#include "game_master.hpp"

GameMaster::GameMaster() : currentPlayer(1) {}

void GameMaster::make_move(int x, int y) {
    if (board[x][y] == 0) {
        board[x][y] = currentPlayer;
        if (!check_win(x, y)) {
            switch_player();
        }
    }
}

bool GameMaster::check_win(int x, int y) const {
    return check_line(x, y, 1, 0) ||
           check_line(x, y, 0, 1) ||
           check_line(x, y, 1, 1) ||
           check_line(x, y, 1, -1);
}

bool GameMaster::check_line(int startX, int startY, int dx, int dy) const {
    int count = 0;
    int player = board[startX][startY];
    for (int i = -4; i <= 4; ++i) {
        int x = startX + i * dx;
        int y = startY + i * dy;
        if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() && board[x][y] == player) {
            count++;
            if (count == 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }
    return false;
}

int GameMaster::get_current_player() const {
    return currentPlayer;
}

void GameMaster::switch_player() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

void GameMaster::reset(int size) {
    board = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
    currentPlayer = 1;
}

int GameMaster::get_winner() const {
    return currentPlayer;
}
