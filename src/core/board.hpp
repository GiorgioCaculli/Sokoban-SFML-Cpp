#ifndef SOKOBAN_BOARD_HPP
#define SOKOBAN_BOARD_HPP

#include <vector>
#include <string>

#include "wall.hpp"
#include "box.hpp"
#include "platform.hpp"
#include "player.hpp"

namespace sokoban
{
    namespace core
    {
        class Board
        {
        private:
            const short OFFSET = 64;
            const short SPACE = 64;
            const short LEFT_COLLISION = 1;
            const short RIGHT_COLLISION = 2;
            const short TOP_COLLISION = 3;
            const short BOTTOM_COLLISION = 4;
            std::vector< Wall * > *walls;
            std::vector< Box * > *boxes;
            std::vector< Platform * > *platforms;
            Player *player;

            short w = 0;
            short h = 0;

            bool completed = false;
            std::string level;
        public:
            Board();
            ~Board();

            void init_board();
            void init_world();

            short get_board_width();
            short get_board_height();

            void build_world();

            bool check_wall_collision( Actor *actor, short type );
            bool check_box_collision( short type );

            void is_completed();

            void restart_level();
        };
    }
}

#endif //SOKOBAN_BOARD_HPP
