#ifndef SOKOBAN_CPP_WALL_HPP
#define SOKOBAN_CPP_WALL_HPP

#include "actor.hpp"

namespace sokoban
{
    namespace core
    {
        class Wall : public Actor
        {
        private:
            void init_wall();

        public:
            Wall( int x, int y );

            ~Wall() override;
        };
    }
}

#endif //SOKOBAN_CPP_WALL_HPP
