#ifndef SOKOBAN_BOX_HPP
#define SOKOBAN_BOX_HPP

#include "actor.hpp"

namespace sokoban
{
    namespace core
    {
        class Box : public Actor
        {
        private:
            void init_box();

        public:
            Box( int x, int y );

            ~Box() override;

            void move( int x, int y );
        };
    }
}

#endif //SOKOBAN_BOX_HPP
