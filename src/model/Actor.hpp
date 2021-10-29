#ifndef SOKOBAN_ACTOR_HPP
#define SOKOBAN_ACTOR_HPP

#include <array>
#include <string>
#include <ostream>

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
            float _x; /* La coordonnée X dans la _board */
            float _y; /* La coordonnée Y dans la _board */
            std::array< float, 4 > _asset_coords;
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
            Actor( float x, float y, std::array< float, 4 > asset_coords );
            Actor( const Actor &actor );
            Actor &operator=( const Actor &actor );
            virtual ~Actor() = default;
            float get_x() const;
            void set_x( float x );
            float get_y() const;
            void set_y( float y );
            std::array< float, 4 > get_asset_coords() const;
            void set_asset_coords( std::array< float, 4 > asset_coords );
            virtual ID get_type() const;
            bool is_left_collision( const Actor *actor ) const;
            bool is_right_collision( const Actor *actor ) const;
            bool is_top_collision( const Actor *actor ) const;
            bool is_bottom_collision( const Actor *actor ) const;
            virtual std::string to_string() const;
            friend std::ostream &operator<<( std::ostream &os, const Actor &actor );
            bool operator==( const Actor &actor ) const;
            bool operator!=( const Actor &actor ) const;
        };
    }
}

#endif //SOKOBAN_ACTOR_HPP
