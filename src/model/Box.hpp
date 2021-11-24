#ifndef SOKOBAN_BOX_HPP
#define SOKOBAN_BOX_HPP

#include "Movable.hpp"

#include <map>
#include <array>
#include <string>
#include <ostream>

namespace sokoban
{
    namespace model
    {
        /**
         * Box class
         * This class is an actor that can move, as such it inherits from the classe Movable
         */
        class Box
                : public Movable
        {
        public:
            enum class Color
            {
                BEIGE_LIGHT,
                BLACK_LIGHT,
                BLUE_LIGHT,
                BROWN_LIGHT,
                BEIGE_DARK,
                BLACK_DARK,
                BLUE_DARK,
                BROWN_DARK,
                WHITE_DARK,
                PURPLE_DARK,
                RED_DARK,
                YELLOW_DARK,
                WHITE_LIGHT,
                PURPLE_LIGHT,
                RED_LIGHT,
                YELLOW_LIGHT
            };
            Box( float x, float y );
            Box( const Box &box );
            Box &operator=( const Box &box );
            ~Box() override;
            ID get_type() const override;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Box &box );
            const std::map< Color, std::array< float, 4>> &get_box_color_map() const;
        private:
            std::map< Color, std::array< float, 4 > > _box_color_map;
        };
    }
}

#endif //SOKOBAN_BOX_HPP
