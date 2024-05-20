#ifndef GAME_MASTER_HPP
#define GAME_MASTER_HPP

#include <vector>

class GameMaster
{
public:
    GameMaster();
    void make_move(int x, int y);
    bool check_win(int x, int y) const;
    bool is_board_full() const;
    int get_current_player() const;
    void switch_player();
    void reset(int size);
    int get_winner() const;

private:
    bool check_line(int startX, int startY, int dx, int dy) const;
    std::vector<std::vector<int>> board;
    int currentPlayer;
};

#endif
