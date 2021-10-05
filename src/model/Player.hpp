#ifndef SOKOBAN_PLAYER_HPP
#define SOKOBAN_PLAYER_HPP

#include <ostream>
#include "Movable.hpp"

namespace sokoban
{
    namespace model
    {
        class Player
                : public Movable
        {
        public:
            Player( int x, int y );
            Player( const Player &player );
            ~Player();
            friend std::ostream &operator<<( std::ostream &os, const Player &player );
        };
    }
}

#endif //SOKOBAN_USER_HPP
