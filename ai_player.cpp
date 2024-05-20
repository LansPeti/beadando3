//MEGJEGYZÉS: NEM TELJESEN OKOS, ÍGY LEGYŐZHETŐ ÉS ÉLVEZHETŐ, LEGINKÁBB A HÁTRÁLTATÁSRA VAN BEÁLLÍTVA
#include "ai_player.hpp"
#include <limits>
#include <vector>
#include <algorithm>

botOnd::botOnd() {}

std::pair<int, int> botOnd::calculate_move(const std::vector<std::vector<int>>& board, int player) {
    int opponent = (player == 1) ? 2 : 1;
    std::pair<int, int> best_move = {-1, -1};
    int best_score = std::numeric_limits<int>::min();

    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] == 0) {


                if (is_winning_move(board, player, row, col)) {
                    return {row, col};
                }

                if (is_winning_move(board, opponent, row, col)) {
                    return {row, col};
                }


                if (is_concerning_move(board, opponent, row, col)) {
                    return {row, col};
                }

                int score = evaluate_move(board, player, row, col);
                if (score > best_score) {
                    best_score = score;
                    best_move = {row, col};
                }
            }
        }
    }


    if (best_move.first == -1) {
        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[row].size(); ++col) {
                if (board[row][col] == 0) {
                    return {row, col};
                }
            }
        }
    }

    return best_move;
}

int botOnd::evaluate_move(const std::vector<std::vector<int>>& board, int player, int row, int col) {
    std::vector<std::vector<int>> temp_board = board;
    temp_board[row][col] = player;
    return evaluate_board(temp_board, player);
}

int botOnd::evaluate_board(const std::vector<std::vector<int>>& board, int player) {
    int score = 0;
    int opponent = (player == 1) ? 2 : 1;

    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] == player) {
                score += count_consecutive(board, player, row, col, 1, 0);
                score += count_consecutive(board, player, row, col, 0, 1);
                score += count_consecutive(board, player, row, col, 1, 1);
                score += count_consecutive(board, player, row, col, 1, -1);
            } else if (board[row][col] == opponent) {
                score -= count_consecutive(board, opponent, row, col, 1, 0);
                score -= count_consecutive(board, opponent, row, col, 0, 1);
                score -= count_consecutive(board, opponent, row, col, 1, 1);
                score -= count_consecutive(board, opponent, row, col, 1, -1);
            }
        }
    }
    return score;
}


int botOnd::count_consecutive(const std::vector<std::vector<int>>& board, int player, int row, int col, int d_row, int d_col) {
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


bool botOnd::is_winning_move(const std::vector<std::vector<int>>& board, int player, int row, int col) {
    return (count_consecutive(board, player, row, col, 1, 0) >= 4 ||
            count_consecutive(board, player, row, col, 0, 1) >= 4 ||
            count_consecutive(board, player, row, col, 1, 1) >= 4 ||
            count_consecutive(board, player, row, col, 1, -1) >= 4);
}


bool botOnd::is_concerning_move(const std::vector<std::vector<int>>& board, int player, int row, int col) {

    return (count_threat(board, player, row, col, 1, 0) >= 2 ||
            count_threat(board, player, row, col, 0, 1) >= 2 ||
            count_threat(board, player, row, col, 1, 1) >= 2 ||
            count_threat(board, player, row, col, 1, -1) >= 2);
}


int botOnd::count_threat(const std::vector<std::vector<int>>& board, int player, int row, int col, int d_row, int d_col) {
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
