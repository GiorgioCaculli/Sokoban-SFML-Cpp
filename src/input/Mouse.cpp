#include <input/Mouse.hpp>

using namespace sokoban::input;

Mouse::Mouse()
= default;

Mouse::Mouse( const Mouse& m )
= default;

Mouse& Mouse::operator=( const Mouse& m )
{
    if( this != &m )
    {
        /* Fill with variables to copy */
    }
    return *this;
}

Mouse::~Mouse()
= default;

bool Mouse::pressing( const sf::Event& event, const sf::Mouse::Button& button, const sf::Transformable& item, const std::function<bool()>&& c )
{
    if ( const auto *buttonPressed = event.getIf<sf::Event::MouseButtonPressed>() )
    {
        if ( buttonPressed->button == button && buttonPressed->position.x <= item.getPosition().x && buttonPressed->position.y <= item.getPosition().y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::pressing( const sf::Event& event, const sf::Mouse::Button& button, const ui::gui::Component::Ptr& item,
    const std::function<bool()>&& c )
{
    if ( const auto *buttonPressed = event.getIf<sf::Event::MouseButtonPressed>() )
    {
        if ( buttonPressed->button == button && buttonPressed->position.x <= item->getPosition().x && buttonPressed->position.y <= item->getPosition().y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::pressing( const sf::Event& event, const sf::Mouse::Button& button, const sf::RenderWindow& item, const std::function<bool()>&& c )
{
    if ( const auto *buttonPressed = event.getIf<sf::Event::MouseButtonPressed>() )
    {
        if ( buttonPressed->button == button && buttonPressed->position.x <= item.getSize().x && buttonPressed->position.y <= item.getSize().y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::releasing( const sf::Event& event, const sf::Mouse::Button& button, const sf::Transformable& item, const std::function<bool()>&& c)
{
    if ( const auto *buttonReleased = event.getIf<sf::Event::MouseButtonReleased>() )
    {
        if ( buttonReleased->button == button && buttonReleased->position.x <= item.getPosition().x && buttonReleased->position.y <= item.getPosition().y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::releasing( const sf::Event& event, const sf::Mouse::Button& button, const ui::gui::Component::Ptr& item,
    const std::function<bool()>&& c )
{
    if ( const auto *buttonPressed = event.getIf<sf::Event::MouseButtonReleased>() )
    {
        if ( buttonPressed->button == button && buttonPressed->position.x <= item->getPosition().x && buttonPressed->position.y <= item->getPosition().y )
        {
            return c();
        }
    }
    return false;
}

bool Mouse::releasing( const sf::Event& event, const sf::Mouse::Button& button, const sf::RenderWindow& item, const std::function<bool()>&& c )
{
    if ( const auto *buttonReleased = event.getIf<sf::Event::MouseButtonReleased>() )
    {
        if ( buttonReleased->button == button && buttonReleased->position.x <= item.getSize().x && buttonReleased->position.y <= item.getSize().y)
        {
            return c();
        }
    }
    return false;
}
