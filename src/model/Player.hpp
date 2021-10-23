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
            enum Face
            {
                NORTH,
                SOUTH,
                EAST,
                WEST
            };
            Player( int x, int y );
            Player( const Player &player );
            Player &operator=( const Player &player );
            ~Player() override;
            ID get_type() const override;
            void set_face( const Face &face );
            Face get_face() const;
            friend std::ostream &operator<<( std::ostream &os, const Player &player );
        private:
            Face current_face;
        };
    }
}

#endif //SOKOBAN_USER_HPP
