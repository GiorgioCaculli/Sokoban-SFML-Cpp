#ifndef SOKOBAN_MOVABLE_HPP
#define SOKOBAN_MOVABLE_HPP

#include "Actor.hpp"

#include <array>
#include <string>
#include <ostream>

/**
 * Class that handles actors capable of moving
 * This class inherits from Actor
 */
namespace sokoban
{
    namespace core
    {
        class Movable
                : public Actor
        {
        public:
            Movable( float x, float y );
            Movable( const Movable &movable );
            Movable &operator=( const Movable &movable );
            ~Movable() override = default;
            void move( float x, float y );
            ID get_type() const override = 0;
            std::string to_string() const override;
        };
    }
}

#endif //SOKOBAN_MOVABLE_HPP
