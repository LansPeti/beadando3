#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include <vector>
#include <utility>

class AIPlayer {
public:
    AIPlayer();
    std::pair<int, int> calculate_move(const std::vector<std::vector<int>>& board, int current_player);
private:
    int evaluate_move(const std::vector<std::vector<int>>& board, int row, int col, int player);
    int evaluate_board(const std::vector<std::vector<int>>& board, int player);
    int count_consecutive(const std::vector<std::vector<int>>& board, int row, int col, int player, int d_row, int d_col);
    bool is_winning_move(const std::vector<std::vector<int>>& board, int row, int col, int player);
    bool is_moves_left(const std::vector<std::vector<int>>& board);
};

#endif
