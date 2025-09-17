#ifndef SOKOBAN_KEYBOARD_HPP
#define SOKOBAN_KEYBOARD_HPP
#include <SFML/Window/Event.hpp>

#include <functional>
#include <vector>

namespace sokoban::input
{
    class Keyboard
    {
    private:
    public:
        Keyboard();
        Keyboard( const Keyboard& k );
        Keyboard& operator=( const Keyboard& k );
        ~Keyboard();
        bool pressing( const sf::Event&, const std::vector< sf::Keyboard::Scancode >&, const std::function<bool()>&& ) const;
        bool releasing( const sf::Event&, const std::vector< sf::Keyboard::Scancode >&, const std::function<bool()>&& ) const;
        template< typename T >
        std::string to_string( const T& value );

        std::string to_string( sf::Keyboard::Scancode key );
    };
}

#endif //SOKOBAN_KEYBOARD_HPP
