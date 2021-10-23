#ifndef SOKOBAN_WALL_HPP
#define SOKOBAN_WALL_HPP

#include <ostream>
#include "Actor.hpp"

namespace sokoban
{
    namespace model
    {
        class Wall
                : public Actor
        {
        public:
            Wall( int x, int y );
            Wall( const Wall &wall );
            Wall &operator=( const Wall &wall );
            ~Wall() override;
            ID get_type() const override;
            friend std::ostream &operator<<( std::ostream &os, const Wall &wall );
        };
    }
}

#endif //SOKOBAN_WALL_HPP
