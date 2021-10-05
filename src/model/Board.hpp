#ifndef SOKOBAN_BOARD_HPP
#define SOKOBAN_BOARD_HPP

#include "Actor.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "Player.hpp"
#include "Platform.hpp"

#include <vector>
#include <ostream>

namespace sokoban
{
    namespace model
    {
        class Board
        {
        private:
            std::vector< Box * > *boxes;
            std::vector< Wall * > *walls;
            std::vector< Platform * > *platforms;
            Player *player;
            int width;
            int height;
            void init_board();
            void init_world();
            void build_world();
            bool check_wall_collision( Actor *actor, int type );
            bool check_bag_collision( int type );
        public:
            Board();
            Board( const Board &board );
            ~Board();
            int get_board_width() const;
            int get_board_height() const;
            void is_completed() const;
            void restart_level() const;
            friend std::ostream &operator<<( std::ostream &os, const Board &board );
        };
    }
}

#endif //SOKOBAN_BOARD_HPP
