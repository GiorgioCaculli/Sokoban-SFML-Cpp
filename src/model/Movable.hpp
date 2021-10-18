#ifndef SOKOBAN_MOVABLE_HPP
#define SOKOBAN_MOVABLE_HPP

#include <ostream>
#include <string>
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
            Movable( int x, int y, std::string asset );
            Movable( const Movable &movable );
            virtual ~Movable();
            void move( int x, int y );
            virtual ID get_type() const;
            friend std::ostream &operator<<( std::ostream &os, const Movable &movable );
        };
    }
}

#endif //SOKOBAN_MOVABLE_HPP
