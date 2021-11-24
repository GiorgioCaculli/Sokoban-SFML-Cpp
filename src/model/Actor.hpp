#ifndef SOKOBAN_ACTOR_HPP
#define SOKOBAN_ACTOR_HPP

#include <array>
#include <string>
#include <ostream>

namespace sokoban
{
    namespace model
    {
        /**
         * Actor class
         * Parent class for any actor that will be displayed throughout the game
         * Parent class of both movable and non movable actors
         */
        class Actor
        {
        private:
            float _x; /** The X coordinate on the board */
            float _y; /** The Y coordinate on the board */
            std::array< float, 4 > _asset_coords; /** The asset's coordinates on the sprite sheet */
        public:
            enum ID /** We consider there to be 4 types of actors */
            {
                BOX, /** A box */
                PLATFORM, /** A platform on which we put the box */
                PLAYER, /** A player */
                WALL /** A wall */
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
            virtual ID get_type() const = 0;
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
