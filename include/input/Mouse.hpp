#ifndef SOKOBAN_MOUSE_HPP
#define SOKOBAN_MOUSE_HPP
#include <SFML/Window/Event.hpp>

#include <functional>
#include <SFML/Graphics/Transformable.hpp>

namespace sokoban::input
{
    class Mouse
    {
        public:
        Mouse();
        ~Mouse();
        bool pressing( const sf::Event&, const sf::Mouse::Button&, const sf::Transformable&, std::function<bool()>&& );
        bool releasing( const sf::Event&, const sf::Mouse::Button&, const sf::Transformable&, std::function<bool()>&& );
    };
}

#endif //SOKOBAN_MOUSE_HPP
