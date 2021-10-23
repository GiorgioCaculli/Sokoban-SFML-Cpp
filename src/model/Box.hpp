#ifndef SOKOBAN_BOX_HPP
#define SOKOBAN_BOX_HPP

#include <ostream>
#include "Movable.hpp"

namespace sokoban
{
    namespace model
    {
        class Box
                : public Movable
        {
        public:
            Box( int x, int y );
            Box( const Box &box );
            Box &operator=( const Box &box );
            ~Box() override;
            ID get_type() const override;
            friend std::ostream &operator<<( std::ostream &os, const Box &box );
        };
    }
}

#endif //SOKOBAN_BOX_HPP
