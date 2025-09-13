#ifndef SOKOBAN_UTILITY_HPP
#define SOKOBAN_UTILITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <sstream>

#ifndef SOKOBAN_UTILITY_INL
#define SOKOBAN_UTILITY_INL

/**
 * Function meant to return a stringstream to stream.
 * @tparam T The nature of the entity that will call this function
 * @param value The value to insert into the stringstream
 * @return The stringstream in string format
 */
template< typename T >
std::string to_string( const T& value )
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

#endif //SOKOBAN_UTILITY_INL

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
}


#endif //SOKOBAN_UTILITY_HPP
