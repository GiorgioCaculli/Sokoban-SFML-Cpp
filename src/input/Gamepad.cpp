#include <input/Gamepad.hpp>

using namespace sokoban::input;

Gamepad::Gamepad()
= default;

Gamepad::Gamepad( const Gamepad& g )
= default;

Gamepad& Gamepad::operator=( const Gamepad& g )
{
    if( this != &g )
    {
        /* Fill with variables to copy */
    }
    return *this;
}

Gamepad::~Gamepad()
= default;
