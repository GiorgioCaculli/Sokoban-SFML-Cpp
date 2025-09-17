#ifndef SOKOBAN_GAMEPAD_HPP
#define SOKOBAN_GAMEPAD_HPP
#include <SFML/Window/Event.hpp>

namespace sokoban::input
{
    class Gamepad
    {
    private:
    public:
        Gamepad();
        Gamepad( const Gamepad& g );
        Gamepad& operator=( const Gamepad& g );
        ~Gamepad();
    };
}

#endif //SOKOBAN_GAMEPAD_HPP
