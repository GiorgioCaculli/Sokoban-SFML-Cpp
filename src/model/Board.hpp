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
        /**
         * Board class
         * Meant to build the layout of the leve that the player will be playing
         */
        class Board
        {
        private:
            std::string _level; /** The skeleton of the level */
            std::vector< Box * > _boxes; /** All the boxes in the level */
            std::vector< Wall * > _walls; /** All the walls in the game */
            std::vector< Platform * > _platforms; /** All the platforms in the game */
            Player *_player; /** The main character of the game */
            std::vector< Actor * > _world; /** Every actor in the game */
            float _width; /** The board's maximum width */
            float _height; /** The board's maximum height */
            bool _completed; /** Whether the game is completed */
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
            explicit Board( const std::string &lvl );
            Board( const Board &board );
            Board &operator=( const Board &board );
            ~Board();
            bool check_wall_collision( Actor *actor, int type );
            bool check_box_collision( int type );
            float get_board_width() const;
            float get_board_height() const;
            bool is_completed() const;
            std::vector< Actor * > get_world();
            friend std::ostream &operator<<( std::ostream &os, const Board &board );
        };
    }
}

#endif //SOKOBAN_BOARD_HPP
