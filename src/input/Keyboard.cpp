#include <input/Keyboard.hpp>

#include <algorithm>

using namespace sokoban::input;

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

bool Keyboard::pressing( const sf::Event& event, const std::vector< sf::Keyboard::Scancode >& keys, std::function<bool()>&& c ) const
{
    if ( const auto *key_pressed = event.getIf<sf::Event::KeyPressed>())
    {
        if ( !keys.empty() && std::ranges::find( keys, key_pressed->scancode) != keys.end() )
        {
            return c();
        }
    }
    return false;
}

bool Keyboard::releasing( const sf::Event& event, const std::vector< sf::Keyboard::Scancode >& keys, std::function<bool()>&& c ) const
{
    if ( const auto *key_released = event.getIf<sf::Event::KeyReleased>())
    {
        if ( !keys.empty() && std::ranges::find( keys, key_released->scancode) != keys.end() )
        {
            return c();
        }
    }
    return false;
}

/**
 * Function meant to return a keyboard key to string
 * @param key The key to be converted
 * @return The key in textual form
 */
std::string Keyboard::to_string( const sf::Keyboard::Scancode key )
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
