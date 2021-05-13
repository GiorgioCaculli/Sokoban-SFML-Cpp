#ifndef SOKOBAN_PLATFORM_HPP
#define SOKOBAN_PLATFORM_HPP

#include "actor.hpp"

namespace com
{
    namespace masticass
    {
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
                    ~Platform();
                };
            }
        }
    }
}

#endif //SOKOBAN_PLATFORM_HPP
