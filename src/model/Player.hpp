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
            std::array< std::array< int, 4 >, 10 > get_animations() const;
            friend std::ostream &operator<<( std::ostream &os, const Player &player );
        private:
            Face _current_face;
            std::array< std::array< int, 4 >, 10 > _animations;
        };
    }
}

#endif //SOKOBAN_USER_HPP
