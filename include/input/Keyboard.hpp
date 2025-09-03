#ifndef SOKOBAN_KEYBOARD_HPP
#define SOKOBAN_KEYBOARD_HPP
#include <SFML/Window/Event.hpp>

#include <functional>

namespace sokoban::input
{
    class Keyboard
    {
    private:
        sf::Event::KeyPressed *_key_pressed;
        sf::Event::KeyReleased *_key_released;
    public:
        Keyboard();
        ~Keyboard();
        bool pressing( sf::Keyboard::Scancode, std::function<bool()>&& ) const;
        bool releasing( sf::Keyboard::Scancode, std::function<bool()>&& ) const;
        template< typename T >
        std::string to_string( const T& value );

        std::string to_string( sf::Keyboard::Scancode key );
    };
}

#endif //SOKOBAN_KEYBOARD_HPP
