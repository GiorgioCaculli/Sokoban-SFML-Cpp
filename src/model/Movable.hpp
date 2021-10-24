#ifndef SOKOBAN_MOVABLE_HPP
#define SOKOBAN_MOVABLE_HPP

#include <ostream>
#include <array>
#include "Actor.hpp"

/*
 * Classe qui gère les acteurs capables de se déplacer.
 * Cette classe hérite de la classe Actor
 */
namespace sokoban
{
    namespace model
    {
        class Movable
                : public Actor
        {
        public:
            Movable( int x, int y, std::array< int, 4 > asset_coords );
            Movable( const Movable &movable );
            Movable &operator=( const Movable &movable );
            ~Movable() override = default;
            void move( int x, int y );
            ID get_type() const override = 0;
            friend std::ostream &operator<<( std::ostream &os, const Movable &movable );
        };
    }
}

#endif //SOKOBAN_MOVABLE_HPP
