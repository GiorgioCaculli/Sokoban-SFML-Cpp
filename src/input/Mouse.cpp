#include <input/Mouse.hpp>

using namespace sokoban::input;

Mouse::Mouse()
= default;

Mouse::~Mouse()
= default;

bool Mouse::pressing( const sf::Event& event, const sf::Mouse::Button& button, const sf::Transformable& item, std::function<bool()>&& c )
{
    if ( const auto *buttonPressed = event.getIf<sf::Event::MouseButtonPressed>() )
    {
        if ( buttonPressed->button == button && item.getPosition().x >= buttonPressed->position.x && item.getPosition().y >= buttonPressed->position.y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::pressing( const sf::Event& event, const sf::Mouse::Button& button, const ui::gui::Component::Ptr& item,
    std::function<bool()>&& c )
{
    if ( const auto *buttonPressed = event.getIf<sf::Event::MouseButtonPressed>() )
    {
        if ( buttonPressed->button == button && item->getPosition().x >= buttonPressed->position.x && item->getPosition().y >= buttonPressed->position.y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::releasing( const sf::Event& event, const sf::Mouse::Button& button, const sf::Transformable& item, std::function<bool()>&& c)
{
    if ( const auto *buttonReleased = event.getIf<sf::Event::MouseButtonReleased>() )
    {
        if ( buttonReleased->button == button && item.getPosition().x >= buttonReleased->position.x && item.getPosition().y >= buttonReleased->position.y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::releasing( const sf::Event& event, const sf::Mouse::Button& button, const ui::gui::Component::Ptr& item,
    std::function<bool()>&& c )
{
    if ( const auto *buttonPressed = event.getIf<sf::Event::MouseButtonReleased>() )
    {
        if ( buttonPressed->button == button && item->getPosition().x >= buttonPressed->position.x && item->getPosition().y >= buttonPressed->position.y )
        {
            return c();
        }
    }
    return false;
}
