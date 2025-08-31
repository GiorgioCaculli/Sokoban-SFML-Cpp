#include <ui/gui/Utility.hpp>
#include <ui/gui/Animation.hpp>
#include <ui/gui/components/Button.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>

using namespace sokoban::ui::gui;

namespace
{
    std::default_random_engine create_Random_Engine()
    {
        const auto seed = static_cast< unsigned long >( std::time( nullptr ) );
        return std::default_random_engine( seed );
    }

    auto Random_Engine = create_Random_Engine();
}

/**
 * Function meant to return a keyboard key to string
 * @param key The key to be converted
 * @return The key in textual form
 */
std::string Utility::to_string( const sf::Keyboard::Scancode key )
{
#define BOOK_KEY_TO_STRING_CASE( KEY ) case sf::Keyboard::Scancode::KEY: return #KEY;

    switch ( key )
    {
        BOOK_KEY_TO_STRING_CASE( Unknown )
        BOOK_KEY_TO_STRING_CASE( A )
        BOOK_KEY_TO_STRING_CASE( B )
        BOOK_KEY_TO_STRING_CASE( C )
        BOOK_KEY_TO_STRING_CASE( D )
        BOOK_KEY_TO_STRING_CASE( E )
        BOOK_KEY_TO_STRING_CASE( F )
        BOOK_KEY_TO_STRING_CASE( G )
        BOOK_KEY_TO_STRING_CASE( H )
        BOOK_KEY_TO_STRING_CASE( I )
        BOOK_KEY_TO_STRING_CASE( J )
        BOOK_KEY_TO_STRING_CASE( K )
        BOOK_KEY_TO_STRING_CASE( L )
        BOOK_KEY_TO_STRING_CASE( M )
        BOOK_KEY_TO_STRING_CASE( N )
        BOOK_KEY_TO_STRING_CASE( O )
        BOOK_KEY_TO_STRING_CASE( P )
        BOOK_KEY_TO_STRING_CASE( Q )
        BOOK_KEY_TO_STRING_CASE( R )
        BOOK_KEY_TO_STRING_CASE( S )
        BOOK_KEY_TO_STRING_CASE( T )
        BOOK_KEY_TO_STRING_CASE( U )
        BOOK_KEY_TO_STRING_CASE( V )
        BOOK_KEY_TO_STRING_CASE( W )
        BOOK_KEY_TO_STRING_CASE( X )
        BOOK_KEY_TO_STRING_CASE( Y )
        BOOK_KEY_TO_STRING_CASE( Z )
        BOOK_KEY_TO_STRING_CASE( Num0 )
        BOOK_KEY_TO_STRING_CASE( Num1 )
        BOOK_KEY_TO_STRING_CASE( Num2 )
        BOOK_KEY_TO_STRING_CASE( Num3 )
        BOOK_KEY_TO_STRING_CASE( Num4 )
        BOOK_KEY_TO_STRING_CASE( Num5 )
        BOOK_KEY_TO_STRING_CASE( Num6 )
        BOOK_KEY_TO_STRING_CASE( Num7 )
        BOOK_KEY_TO_STRING_CASE( Num8 )
        BOOK_KEY_TO_STRING_CASE( Num9 )
        BOOK_KEY_TO_STRING_CASE( Escape )
        BOOK_KEY_TO_STRING_CASE( LControl )
        BOOK_KEY_TO_STRING_CASE( LShift )
        BOOK_KEY_TO_STRING_CASE( LAlt )
        BOOK_KEY_TO_STRING_CASE( LSystem )
        BOOK_KEY_TO_STRING_CASE( RControl )
        BOOK_KEY_TO_STRING_CASE( RShift )
        BOOK_KEY_TO_STRING_CASE( RAlt )
        BOOK_KEY_TO_STRING_CASE( RSystem )
        BOOK_KEY_TO_STRING_CASE( Menu )
        BOOK_KEY_TO_STRING_CASE( LBracket )
        BOOK_KEY_TO_STRING_CASE( RBracket )
        BOOK_KEY_TO_STRING_CASE( Semicolon )
        BOOK_KEY_TO_STRING_CASE( Comma )
        BOOK_KEY_TO_STRING_CASE( Period )
        BOOK_KEY_TO_STRING_CASE( Apostrophe )
        BOOK_KEY_TO_STRING_CASE( Slash )
        BOOK_KEY_TO_STRING_CASE( Backslash )
        BOOK_KEY_TO_STRING_CASE( Equal )
        BOOK_KEY_TO_STRING_CASE( Space )
        BOOK_KEY_TO_STRING_CASE( Enter )
        BOOK_KEY_TO_STRING_CASE( Backspace )
        BOOK_KEY_TO_STRING_CASE( Tab )
        BOOK_KEY_TO_STRING_CASE( PageUp )
        BOOK_KEY_TO_STRING_CASE( PageDown )
        BOOK_KEY_TO_STRING_CASE( End )
        BOOK_KEY_TO_STRING_CASE( Home )
        BOOK_KEY_TO_STRING_CASE( Insert )
        BOOK_KEY_TO_STRING_CASE( Delete )
        BOOK_KEY_TO_STRING_CASE( Left )
        BOOK_KEY_TO_STRING_CASE( Right )
        BOOK_KEY_TO_STRING_CASE( Up )
        BOOK_KEY_TO_STRING_CASE( Down )
        BOOK_KEY_TO_STRING_CASE( Numpad0 )
        BOOK_KEY_TO_STRING_CASE( Numpad1 )
        BOOK_KEY_TO_STRING_CASE( Numpad2 )
        BOOK_KEY_TO_STRING_CASE( Numpad3 )
        BOOK_KEY_TO_STRING_CASE( Numpad4 )
        BOOK_KEY_TO_STRING_CASE( Numpad5 )
        BOOK_KEY_TO_STRING_CASE( Numpad6 )
        BOOK_KEY_TO_STRING_CASE( Numpad7 )
        BOOK_KEY_TO_STRING_CASE( Numpad8 )
        BOOK_KEY_TO_STRING_CASE( Numpad9 )
        BOOK_KEY_TO_STRING_CASE( F1 )
        BOOK_KEY_TO_STRING_CASE( F2 )
        BOOK_KEY_TO_STRING_CASE( F3 )
        BOOK_KEY_TO_STRING_CASE( F4 )
        BOOK_KEY_TO_STRING_CASE( F5 )
        BOOK_KEY_TO_STRING_CASE( F6 )
        BOOK_KEY_TO_STRING_CASE( F7 )
        BOOK_KEY_TO_STRING_CASE( F8 )
        BOOK_KEY_TO_STRING_CASE( F9 )
        BOOK_KEY_TO_STRING_CASE( F10 )
        BOOK_KEY_TO_STRING_CASE( F11 )
        BOOK_KEY_TO_STRING_CASE( F12 )
        BOOK_KEY_TO_STRING_CASE( F13 )
        BOOK_KEY_TO_STRING_CASE( F14 )
        BOOK_KEY_TO_STRING_CASE( F15 )
        BOOK_KEY_TO_STRING_CASE( Pause )
        default:
            break;
            //case sf::Keyboard::KeyCount: // TODO: No idea why this breaks, migration documentation does not mention anything about this but I will figure it out
            //break;
    }
    return "";
}

/**
 * Function that sets a sprite's origin in its center
 * @param sprite The sprite to center
 */
void Utility::center_origin( sf::Sprite& sprite )
{
    const sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin( sf::Vector2f(
        std::floor( bounds.position.x + bounds.size.x / 2.f ),
        std::floor( bounds.position.y + bounds.size.y / 2.f )
    ) );
}

/**
 * Function that sets a text's origin in its center
 * @param text The text to center
 */
void Utility::center_origin( sf::Text& text )
{
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin( sf::Vector2f(
        std::floor( bounds.position.x + bounds.size.x / 2.f ),
        std::floor( bounds.position.y + bounds.size.y / 2.f )
    ) );
}

/**
 * Function that sets the animation's origin in its center
 * @param animation The animation to center
 */
void Utility::center_origin( Animation& animation )
{
    const sf::FloatRect bounds = animation.get_local_bounds();
    animation.setOrigin( sf::Vector2f(
        std::floor( bounds.position.x + bounds.size.x / 2.f ),
        std::floor( bounds.position.y + bounds.size.y / 2.f )
    ) );
}

/**
 * Function to convert from Radian to Degrees
 * @param radian The radian value to convert
 * @return The radian value in degrees form
 */
float Utility::to_degree( const float radian )
{
    return 100.f / M_PI * radian;
}

/**
 * Function to convert from Degree to Radian
 * @param degree The degree value to convert
 * @return The degree value in radian form
 */
float Utility::to_radian( const float degree )
{
    return M_PI / 100.f * degree;
}

/**
 * Random integer generator
 * @param exclusive_max The maximum value we wish to obtain
 * @return A value from 0 to Max
 */
int Utility::random_int( const int exclusive_max )
{
    std::uniform_int_distribution dist( 0, exclusive_max - 1 );
    return dist( Random_Engine );
}

/**
 * Function to calculate the distance between within a vector
 * @param vector The vecto's to calculate
 * @return X * X + Y * Y
 */
float Utility::length( const sf::Vector2f vector )
{
    return std::sqrt( vector.x * vector.x + vector.y * vector.y );
}

/**
 * Unit calculator based on the length of a vector and a vector itself
 */
sf::Vector2f Utility::unit_vector( const sf::Vector2f vector )
{
    assert( vector != sf::Vector2f( 0.f, 0.f ) );
    return vector / length( vector );
}
