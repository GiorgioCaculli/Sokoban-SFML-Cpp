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

        static void center_origin( sf::Sprite& sprite );

        static void center_origin( sf::Text& text );

        static void center_origin( Animation& animation );

        float to_degree( float radian ) const;

        float to_radian( float degree ) const;

        int random_int( int exclusive_max ) const;

        float length( sf::Vector2f vector ) const;

        sf::Vector2f unit_vector( sf::Vector2f vector ) const;
    };

#include <ui/Utility.inl>
}


#endif //SOKOBAN_UTILITY_HPP
