#ifndef SOKOBAN_BOX_HPP
#define SOKOBAN_BOX_HPP

#include "Movable.hpp"

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
            Box( float x, float y );
            Box( const Box &box );
            Box &operator=( const Box &box );
            ~Box() override;
            ID get_type() const override;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Box &box );
        };
    }
}

#endif //SOKOBAN_BOX_HPP
