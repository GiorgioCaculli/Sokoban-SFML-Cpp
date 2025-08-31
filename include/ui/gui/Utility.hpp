#ifndef SOKOBAN_UTILITY_HPP
#define SOKOBAN_UTILITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <sstream>

namespace sf
{
    class Sprite;
    class Text;
}


namespace sokoban::ui::gui
{
    class Animation;

    class Utility
    {
    public:
        template< typename T >
        std::string to_string( const T& value );

        std::string to_string( sf::Keyboard::Scancode key );

        static void center_origin( sf::Sprite& sprite );

        static void center_origin( sf::Text& text );

        static void center_origin( Animation& animation );

        float to_degree( float radian );

        float to_radian( float degree );

        int random_int( int exclusive_max );

        float length( sf::Vector2f vector );

        sf::Vector2f unit_vector( sf::Vector2f vector );
    };

#include "ui/Utility.inl"
}


#endif //SOKOBAN_UTILITY_HPP
