#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include <vector>
#include <utility>

class AIPlayer {
public:
    AIPlayer();
    std::pair<int, int> calculate_move(const std::vector<std::vector<int>>& board, int player);
private:
    int evaluate_move(const std::vector<std::vector<int>>& board, int player, int row, int col);
    int evaluate_board(const std::vector<std::vector<int>>& board, int player);
    int count_consecutive(const std::vector<std::vector<int>>& board, int player, int row, int col, int d_row, int d_col);
    int count_threat(const std::vector<std::vector<int>>& board, int player, int row, int col, int d_row, int d_col);
    bool is_winning_move(const std::vector<std::vector<int>>& board, int player, int row, int col);
    bool is_threatening_move(const std::vector<std::vector<int>>& board, int player, int row, int col);
    bool is_concerning_move(const std::vector<std::vector<int>>& board, int player, int row, int col);
};

#endif
