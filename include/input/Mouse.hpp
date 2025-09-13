#ifndef SOKOBAN_MOUSE_HPP
#define SOKOBAN_MOUSE_HPP
#include <SFML/Window/Event.hpp>

#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <gui/components/Component.hpp>

namespace sokoban::input
{
    class Mouse
    {
    public:
        Mouse();
        ~Mouse();
        bool pressing( const sf::Event&, const sf::Mouse::Button&, const sf::Transformable&, const std::function<bool()>&& );
        bool pressing( const sf::Event&, const sf::Mouse::Button&, const ui::gui::Component::Ptr&, const std::function<bool()>&& );
        bool pressing( const sf::Event&, const sf::Mouse::Button&, const sf::RenderWindow&, const std::function<bool()>&& );
        bool releasing( const sf::Event&, const sf::Mouse::Button&, const sf::Transformable&, const std::function<bool()>&& );
        bool releasing( const sf::Event&, const sf::Mouse::Button&, const ui::gui::Component::Ptr&, const std::function<bool()>&& );
        bool releasing( const sf::Event&, const sf::Mouse::Button&, const sf::RenderWindow&, const std::function<bool()>&& );
    };
}

#endif //SOKOBAN_MOUSE_HPP
