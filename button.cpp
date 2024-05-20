#include "button.hpp"
#include "graphics.hpp"

Button::Button(int x, int y, int width, int height, const std::string &label, std::function<void()> action)
    : Widget(x, y, width, height), label(label), action(action) {}

void Button::draw() const {
    genv::gout << genv::move_to(x, y) << genv::color(200, 200, 200) << genv::box(width, height);
    genv::gout << genv::move_to(x + width / 2 - genv::gout.twidth(label) / 2, y + height / 2 + genv::gout.cdescent() / 2) << genv::color(0, 0, 0) << genv::text(label);
}

void Button::handle_event(const genv::event &ev) {
    if (ev.type == genv::ev_mouse && ev.button == genv::btn_left && ev.pos_x > x && ev.pos_x < x + width && ev.pos_y > y && ev.pos_y < y + height) {
        action();
    }
}

void Button::set_label(const std::string& new_label) {
    label = new_label;
}
