#ifndef SOKOBAN_ACTOR_HPP
#define SOKOBAN_ACTOR_HPP

#include <ostream>

namespace sokoban
{
    namespace model
    {
        class Actor
        {
        private:
            int x;
            int y;
        public:
            Actor( int x, int y );
            Actor( const Actor &actor );
            virtual ~Actor();
            int get_x() const;
            void set_x( int x );
            int get_y() const;
            void set_y( int y );
            friend std::ostream &operator<<( std::ostream &os, const Actor &actor );
        };
    }
}

#endif //SOKOBAN_ACTOR_HPP
