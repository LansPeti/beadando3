#include "ai_player.hpp"
#include <limits>
#include <vector>
#include <algorithm>


AIPlayer::AIPlayer() {}

std::pair<int, int> AIPlayer::calculate_move(const std::vector<std::vector<int>>& board, int player) {
    int opponent = (player == 1) ? 2 : 1;
    std::pair<int, int> best_move = {-1, -1};
    int best_score = std::numeric_limits<int>::min();

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 0) {


                if (is_winning_move(board, player, i, j)) {
                    return {i, j};
                }

                if (is_winning_move(board, opponent, i, j)) {
                    return {i, j};
                }

                if (is_threatening_move(board, opponent, i, j)) {
                    return {i, j};
                }
                if (is_concerning_move(board, opponent, i, j)) {
                    return {i, j};
                }

                int score = evaluate_move(board, player, i, j);
                if (score > best_score) {
                    best_score = score;
                    best_move = {i, j};
                }
            }
        }
    }


    if (best_move.first == -1) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == 0) {
                    return {i, j};
                }
            }
        }
    }

    return best_move;
}

int AIPlayer::evaluate_move(const std::vector<std::vector<int>>& board, int player, int row, int col) {
    std::vector<std::vector<int>> temp_board = board;
    temp_board[row][col] = player;
    return evaluate_board(temp_board, player);
}

int AIPlayer::evaluate_board(const std::vector<std::vector<int>>& board, int player) {
    int score = 0;
    int opponent = (player == 1) ? 2 : 1;


    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == player) {
                score += count_consecutive(board, player, i, j, 1, 0);
                score += count_consecutive(board, player, i, j, 0, 1);
                score += count_consecutive(board, player, i, j, 1, 1);
                score += count_consecutive(board, player, i, j, 1, -1);
            } else if (board[i][j] == opponent) {
                score -= count_consecutive(board, opponent, i, j, 1, 0);
                score -= count_consecutive(board, opponent, i, j, 0, 1);
                score -= count_consecutive(board, opponent, i, j, 1, 1);
                score -= count_consecutive(board, opponent, i, j, 1, -1);
            }
        }
    }
    return score;
}

int AIPlayer::count_consecutive(const std::vector<std::vector<int>>& board, int player, int row, int col, int d_row, int d_col) {
    int count = 0;
    int max_count = 0;

    for (int k = -4; k <= 4; ++k) {
        int r = row + k * d_row;
        int c = col + k * d_col;
        if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size()) {
            if (board[r][c] == player) {
                count++;
                max_count = std::max(max_count, count);
            } else {
                count = 0;
            }
        }
    }

    return max_count;
}

bool AIPlayer::is_winning_move(const std::vector<std::vector<int>>& board, int player, int row, int col) {
    return (count_consecutive(board, player, row, col, 1, 0) >= 4 ||
            count_consecutive(board, player, row, col, 0, 1) >= 4 ||
            count_consecutive(board, player, row, col, 1, 1) >= 4 ||
            count_consecutive(board, player, row, col, 1, -1) >= 4);
}

bool AIPlayer::is_threatening_move(const std::vector<std::vector<int>>& board, int player, int row, int col) {
    return (count_threat(board, player, row, col, 1, 0) >= 3 ||
            count_threat(board, player, row, col, 0, 1) >= 3 ||
            count_threat(board, player, row, col, 1, 1) >= 3 ||
            count_threat(board, player, row, col, 1, -1) >= 3);
}
bool AIPlayer::is_concerning_move(const std::vector<std::vector<int>>& board, int player, int row, int col) {
    return (count_threat(board, player, row, col, 1, 0) >= 2 ||
            count_threat(board, player, row, col, 0, 1) >= 2 ||
            count_threat(board, player, row, col, 1, 1) >= 2 ||
            count_threat(board, player, row, col, 1, -1) >= 2);
}

int AIPlayer::count_threat(const std::vector<std::vector<int>>& board, int player, int row, int col, int d_row, int d_col) {
    int max_count = 0;
    int count = 0;
    bool has_space = false;

    for (int k = -4; k <= 4; ++k) {
        int r = row + k * d_row;
        int c = col + k * d_col;
        if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size()) {
            if (board[r][c] == player) {
                count++;
            } else if (board[r][c] == 0) {
                if (count > 0) {
                    has_space = true;
                    break;
                }
            } else {
                count = 0;
            }
        }
    }

    if (count >= 3 && has_space) {
        max_count = count;
    }

    return max_count;
}
