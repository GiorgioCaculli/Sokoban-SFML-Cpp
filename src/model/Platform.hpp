#ifndef SOKOBAN_PLATFORM_HPP
#define SOKOBAN_PLATFORM_HPP

#include <ostream>
#include "Actor.hpp"

namespace sokoban
{
    namespace model
    {
        class Platform
                : public Actor
        {
        public:
            Platform( int x, int y );
            Platform( const Platform &platform );
            Platform &operator=( const Platform &platform );
            ~Platform() override;
            ID get_type() const override;
            friend std::ostream &operator<<( std::ostream &os, const Platform &platform );
        };
    }
}

#endif //SOKOBAN_PLATFORM_HPP
