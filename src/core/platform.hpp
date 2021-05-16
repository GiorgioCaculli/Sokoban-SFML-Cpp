#ifndef SOKOBAN_PLATFORM_HPP
#define SOKOBAN_PLATFORM_HPP

#include "actor.hpp"

namespace sokoban
{
    namespace core
    {
        class Platform : public Actor
        {
        private:
            void init_platform();

        public:
            Platform( int x, int y );
            ~Platform() override;
        };
    }
}

#endif //SOKOBAN_PLATFORM_HPP
