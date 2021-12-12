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
            Wall( float x, float y );
            Wall( const Wall &wall );
            Wall &operator=( const Wall &wall );
            ~Wall() override;
            ID get_type() const override;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Wall &wall );
        };
    }
}

#endif //SOKOBAN_WALL_HPP
