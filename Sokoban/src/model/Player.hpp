#ifndef SOKOBAN_PLAYER_HPP
#define SOKOBAN_PLAYER_HPP

#include "Movable.hpp"

#include <map>
#include <array>
#include <string>
#include <ostream>

namespace sokoban
{
    namespace model
    {
        class Player
                : public Movable
        {
        public:
            Player( float x, float y );
            Player( const Player &player );
            Player &operator=( const Player &player );
            ~Player() override;
            ID get_type() const override;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Player &player );
        };
    }
}

#endif //SOKOBAN_USER_HPP
