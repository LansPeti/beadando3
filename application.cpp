#include "application.hpp"
#include "graphics.hpp"
#include "main_menu.hpp"
#include "game.hpp"
#include "pause_menu.hpp"
#include "game_over_menu.hpp"
#include "game_master.hpp"
#include <functional>
#include <vector>
#include <iostream>

class ApplicationImpl
{
    enum class State { MAIN_MENU, GAME, PAUSE_MENU, GAME_OVER };

    State current_state;
    MainMenu* main_menu;
    Game* game;
    PauseMenu* pause_menu;
    GameOverMenu* game_over_menu;
    GameMaster master;
    int board_size;
    bool is_bot_game;

public:
    ApplicationImpl()
        : current_state(State::MAIN_MENU),
          main_menu(new MainMenu(0, 0, 1000, 600, [this]()
    {
        start_game(false);
    }, [this]()
    {
        start_game(true);
    })),
    game(nullptr), pause_menu(nullptr), game_over_menu(nullptr), board_size(15), is_bot_game(false) {}

    ~ApplicationImpl()
    {
        delete main_menu;
        delete game;
        delete pause_menu;
        delete game_over_menu;
    }

    void run()
    {
        genv::gout.open(1000, 600);
        genv::event ev;
        while (genv::gin >> ev)
        {
            switch (current_state)
            {
            case State::MAIN_MENU:
                main_menu->handle_event(ev);
                break;
            case State::GAME:
                game->handle_event(ev);
                break;
            case State::PAUSE_MENU:
                pause_menu->handle_event(ev);
                break;
            case State::GAME_OVER:
                game_over_menu->handle_event(ev);
                break;
            }
            genv::gout << genv::move_to(0, 0) << genv::color(0, 0, 0) << genv::box(1000, 600);
            switch (current_state)
            {
            case State::MAIN_MENU:
                main_menu->draw();
                break;
            case State::GAME:
                game->draw();
                break;
            case State::PAUSE_MENU:
                pause_menu->draw();
                break;
            case State::GAME_OVER:
                game_over_menu->draw();
                break;
            }
            genv::gout << genv::refresh;
        }
    }

    void start_game(bool bot)
    {
        is_bot_game = bot;
        board_size = main_menu->get_board_size();
        master.reset(board_size);
        delete game;
        game = new Game(0, 0, board_size * 20, &master, [this]()
        {
            pause_game();
        }, [this](const std::string& winner)
        {
            game_over(winner);
        }, bot);
        current_state = State::GAME;
    }

    void pause_game()
    {
        if (pause_menu == nullptr)
        {
            pause_menu = new PauseMenu(0, 0, 1000, 600, [this]()
            {
                resume_game();
            }, [this]()
            {
                restart_game();
            }, [this]()
            {
                go_to_main_menu();
            });
        }
        current_state = State::PAUSE_MENU;
        game->pause();
    }

    void resume_game()
    {
        current_state = State::GAME;
        game->resume();
    }

    void game_over(const std::string& winner)
    {

        delete game_over_menu;
        game_over_menu = new GameOverMenu(0, 0, 1000, 600, winner, [this]()
        {
            restart_game();
        }, [this]()
        {
            go_to_main_menu();
        });
        current_state = State::GAME_OVER;
    }

    void restart_game()
    {
        start_game(is_bot_game);
    }

    void go_to_main_menu()
    {
        current_state = State::MAIN_MENU;
    }
};

Application::Application() : pimpl(new ApplicationImpl()) {}

Application::~Application()
{
    delete pimpl;
}

void Application::run()
{
    pimpl->run();
}

void Application::game_over(const std::string& winner)
{
    pimpl->game_over(winner);
}
