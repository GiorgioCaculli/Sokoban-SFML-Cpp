#ifndef SOKOBAN_MOVABLE_HPP
#define SOKOBAN_MOVABLE_HPP

#include "Actor.hpp"

#include <array>
#include <string>
#include <ostream>

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
            Movable( float x, float y );
            Movable( const Movable &movable );
            Movable &operator=( const Movable &movable );
            ~Movable() override = default;
            void move( float x, float y );
            ID get_type() const override = 0;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Movable &movable );
        };
    }
}

#endif //SOKOBAN_MOVABLE_HPP
