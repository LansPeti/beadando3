#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include <functional>
#include <string>

class Button : public Widget
{
    std::string label;
    std::function<void()> action;
public:
    Button(int x, int y, int width, int height, const std::string &label, std::function<void()> action);
    void draw() const override;
    void handle_event(const genv::event &ev) override;
    void set_label(const std::string& new_label);
};

#endif
