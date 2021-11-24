#ifndef SOKOBAN_PLATFORM_HPP
#define SOKOBAN_PLATFORM_HPP

#include "Actor.hpp"

#include <map>
#include <array>
#include <string>
#include <ostream>

namespace sokoban
{
    namespace model
    {
        class Platform
                : public Actor
        {
        public:
            enum class Color
            {
                BEIGE,
                BLACK,
                BLUE,
                BROWN,
                WHITE,
                PURPLE,
                RED,
                YELLOW
            };
            Platform( float x, float y );
            Platform( const Platform &platform );
            Platform &operator=( const Platform &platform );
            ~Platform() override;
            ID get_type() const override;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Platform &platform );
            const std::map< Color, std::array< float, 4>> &get_platform_color_map() const;
        private:
            std::map< Color, std::array< float, 4 > > _platform_color_map;
        };
    }
}

#endif //SOKOBAN_PLATFORM_HPP
