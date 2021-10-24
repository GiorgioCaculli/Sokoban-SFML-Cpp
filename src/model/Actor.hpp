#ifndef SOKOBAN_ACTOR_HPP
#define SOKOBAN_ACTOR_HPP

#include <ostream>
#include <array>

/*
 * Classe actor
 * Cette classe est le _parent de tous les objects.
 * Bien des objects qui peuvent bouger, que ces qui sont fixes.
 */
namespace sokoban
{
    namespace model
    {
        class Actor
        {
        private:
            int _x; /* La coordonnée X dans la _board */
            int _y; /* La coordonnée Y dans la _board */
            std::array< int, 4 > _asset_coords;
        public:
            /*
             * On considère 4 acteurs possibles dans le jeu
             * - Une boîte
             * - Une plateforme sur laquelle poser la boîte
             * - Le joueur
             * - Un mur
             */
            enum ID
            {
                BOX,
                PLATFORM,
                PLAYER,
                WALL
            };
            Actor( int x, int y, std::array< int, 4 > asset_coords );
            Actor( const Actor &actor );
            Actor &operator=( const Actor &actor );
            virtual ~Actor() = default;
            int get_x() const;
            void set_x( int x );
            int get_y() const;
            void set_y( int y );
            std::array< int, 4 > get_asset_coords() const;
            void set_asset_coords( std::array< int, 4 > asset_coords );
            virtual ID get_type() const;
            bool is_left_collision( const Actor *actor ) const;
            bool is_right_collision( const Actor *actor ) const;
            bool is_top_collision( const Actor *actor ) const;
            bool is_bottom_collision( const Actor *actor ) const;
            friend std::ostream &operator<<( std::ostream &os, const Actor &actor );
            bool operator==( const Actor &actor ) const;
            bool operator!=( const Actor &actor ) const;
        };
    }
}

#endif //SOKOBAN_ACTOR_HPP
