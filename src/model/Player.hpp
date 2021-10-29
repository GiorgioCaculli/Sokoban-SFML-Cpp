#ifndef SOKOBAN_PLAYER_HPP
#define SOKOBAN_PLAYER_HPP

#include "Movable.hpp"

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
            enum Face
            {
                NORTH,
                SOUTH,
                EAST,
                WEST
            };
            Player( float x, float y );
            Player( const Player &player );
            Player &operator=( const Player &player );
            ~Player() override;
            ID get_type() const override;
            void set_face( const Face &face );
            Face get_face() const;
            std::array< std::array< float, 4 >, 10 > get_animations() const;
            std::string to_string() const override;
            friend std::ostream &operator<<( std::ostream &os, const Player &player );
        private:
            Face _current_face;
            std::array< std::array< float, 4 >, 10 > _animations;
        };
    }
}

#endif //SOKOBAN_USER_HPP
