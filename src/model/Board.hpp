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
            std::vector< Actor * > *world;
            int width;
            int height;
            bool completed;
            void init_board();
            void init_world();
            void build_world();
        public:
            enum
            {
                LEFT_COLLISION,
                RIGHT_COLLISION,
                TOP_COLLISION,
                BOTTOM_COLLISION
            };
            explicit Board( std::string lvl );
            Board();
            Board( const Board &board );
            ~Board();
            bool check_wall_collision( Actor *actor, int type );
            bool check_box_collision( int type );
            int get_board_width() const;
            int get_board_height() const;
            bool is_completed() const;
            void restart_level() const;
            std::vector< Actor * > *get_world();
            friend std::ostream &operator<<( std::ostream &os, const Board &board );
        };
    }
}

#endif //SOKOBAN_BOARD_HPP
