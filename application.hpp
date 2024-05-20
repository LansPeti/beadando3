#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

class ApplicationImpl;

class Application
{
    ApplicationImpl* pimpl;
public:
    Application();
    ~Application();
    void run();
    void game_over(const std::string& winner);
};

#endif
