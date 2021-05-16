#ifndef SOKOBAN_CPP_PLAYER_HPP
#define SOKOBAN_CPP_PLAYER_HPP

#include "actor.hpp"

namespace sokoban
{
    namespace core
    {
        class Player : public Actor
        {
        private:
            void init_player();

        public:
            Player( int x, int y );

            ~Player() override;

            void move( int x, int y );
        };
    }
}

#endif //SOKOBAN_CPP_PLAYER_HPP
