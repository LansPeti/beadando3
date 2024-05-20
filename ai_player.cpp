#include "ai_player.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

AIPlayer::AIPlayer() {
    std::srand(std::time(nullptr));
}

std::pair<int, int> AIPlayer::calculate_move(const std::vector<std::vector<int>>& board, int current_player) {
    int opponent = (current_player == 1) ? 2 : 1;
    std::pair<int, int> best_move = {-1, -1};
    int best_score = std::numeric_limits<int>::min();
    std::vector<std::vector<int>> board_copy = board;


    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board_copy[i][j] == 0) {

                board_copy[i][j] = opponent;
                if (is_winning_move(board_copy, i, j, opponent)) {
                    board_copy[i][j] = current_player;
                    return {i, j};
                }
                board_copy[i][j] = 0;


                board_copy[i][j] = current_player;
                int score = evaluate_board(board_copy, current_player) - evaluate_board(board_copy, opponent);
                board_copy[i][j] = 0;

                if (score > best_score) {
                    best_score = score;
                    best_move = {i, j};
                }
            }
        }
    }


    if (best_move.first == -1) {
        std::vector<std::pair<int, int>> available_moves;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == 0) {
                    available_moves.push_back({i, j});
                }
            }
        }
        if (!available_moves.empty()) {
            int random_index = std::rand() % available_moves.size();
            best_move = available_moves[random_index];
        }
    }

    return best_move;
}

int AIPlayer::evaluate_board(const std::vector<std::vector<int>>& board, int player) {
    int score = 0;


    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == player) {
                score += count_consecutive(board, i, j, player, 1, 0);
                score += count_consecutive(board, i, j, player, 0, 1);
                score += count_consecutive(board, i, j, player, 1, 1);
                score += count_consecutive(board, i, j, player, 1, -1);
            }
        }
    }

    return score;
}

int AIPlayer::count_consecutive(const std::vector<std::vector<int>>& board, int row, int col, int player, int d_row, int d_col) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        int r = row + i * d_row;
        int c = col + i * d_col;
        if (r >= 0 && r < static_cast<int>(board.size()) && c >= 0 && c < static_cast<int>(board[r].size()) && board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    return count == 5 ? 100 : count;
}

bool AIPlayer::is_winning_move(const std::vector<std::vector<int>>& board, int row, int col, int player) {
    return (count_consecutive(board, row, col, player, 1, 0) == 100 ||
            count_consecutive(board, row, col, player, 0, 1) == 100 ||
            count_consecutive(board, row, col, player, 1, 1) == 100 ||
            count_consecutive(board, row, col, player, 1, -1) == 100);
}

bool AIPlayer::is_moves_left(const std::vector<std::vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == 0)
                return true;
        }
    }
    return false;
}
