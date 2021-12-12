#ifndef SOKOBAN_PLATFORM_HPP
#define SOKOBAN_PLATFORM_HPP

#include "Actor.hpp"

#include <map>
#include <array>
#include <string>
#include <ostream>

namespace sokoban
{
    namespace model
    {
        class Platform
                : public Actor
        {
        public:
            Platform( float x, float y );
            Platform( const Platform &platform );
            Platform &operator=( const Platform &platform );
            ~Platform() override;
            ID get_type() const override;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Platform &platform );
        };
    }
}

#endif //SOKOBAN_PLATFORM_HPP
