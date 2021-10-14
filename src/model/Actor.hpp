#ifndef SOKOBAN_ACTOR_HPP
#define SOKOBAN_ACTOR_HPP

#include <ostream>
#include <string>

namespace sokoban
{
    namespace model
    {
        class Actor
        {
        private:
            int x;
            int y;
            std::string asset;
        public:
            enum ID
            {
                BOX,
                PLATFORM,
                PLAYER,
                WALL
            };
            Actor( int x, int y, std::string asset );
            Actor( const Actor &actor );
            virtual ~Actor();
            int get_x() const;
            void set_x( int x );
            int get_y() const;
            void set_y( int y );
            std::string get_asset() const;
            void set_asset( std::string asset );
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
