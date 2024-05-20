#ifndef GAME_HPP
#define GAME_HPP

#include "widget.hpp"
#include "button.hpp"
#include "game_master.hpp"
#include "ai_player.hpp"
#include <vector>
#include <functional>

class Game : public Widget
{
    std::vector<std::vector<int>> board;
    GameMaster *master;
    Button pause_button;
    int board_size;
    bool is_paused;
    std::function<void(const std::string&)> game_over_callback;
    bool is_bot_game;
    botOnd ai_player;
public:
    Game(int x , int y , int size, GameMaster *master, std::function<void()> on_pause, std::function<void(const std::string&)> on_game_over, bool bot_game);
    void draw() const override;
    void handle_event(const genv::event &ev) override;
    void reset();

    void pause();
    void resume();
private:
    void bot_move();
};

#endif
