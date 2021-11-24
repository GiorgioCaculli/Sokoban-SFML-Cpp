#ifndef SOKOBAN_WALL_HPP
#define SOKOBAN_WALL_HPP

#include "Actor.hpp"

#include <map>
#include <array>
#include <string>
#include <ostream>

namespace sokoban
{
    namespace model
    {
        class Wall
                : public Actor
        {
        public:
            enum class Color
            {
                BEIGE,
                BLACK,
                BROWN,
                WHITE
            };
            Wall( float x, float y );
            Wall( const Wall &wall );
            Wall &operator=( const Wall &wall );
            ~Wall() override;
            ID get_type() const override;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Wall &wall );
            const std::map< Color, std::array< float, 4>> &get_wall_color_map() const;
        private:
            std::map< Color, std::array< float, 4 > > _wall_color_map;
        };
    }
}

#endif //SOKOBAN_WALL_HPP
