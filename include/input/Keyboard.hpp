#ifndef SOKOBAN_KEYBOARD_HPP
#define SOKOBAN_KEYBOARD_HPP
#include <SFML/Window/Event.hpp>

namespace sokoban::input
{
    class Keyboard
    {
    private:
        bool _is_key_pressed;
        bool _is_key_released;
        bool _is_key_held;
    public:
        Keyboard();
        ~Keyboard();
    };
}

#endif //SOKOBAN_KEYBOARD_HPP
