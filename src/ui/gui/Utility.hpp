#ifndef SOKOBAN_UTILITY_HPP
#define SOKOBAN_UTILITY_HPP

#include <sstream>

namespace sf
{
    class Sprite;
    class Text;
}

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Utility
            {
            public:
                template< typename T >
                    std::string to_string( const T &value );
                static void center_origin( sf::Sprite &sprite );
                static void center_origin( sf::Text &text );
            };
#include "../Utility.inl"
        }
    }
}

#endif //SOKOBAN_UTILITY_HPP
