#ifndef SOKOBAN_CPP_WALL_HPP
#define SOKOBAN_CPP_WALL_HPP

#include "actor.hpp"

#include <SFML/Graphics.hpp>

namespace sokoban
{
    namespace core
    {
        class Wall : public Actor
        {
        private:
            sf::Texture *texture;
            void init_wall();

        public:
            Wall( float x, float y );

            ~Wall() override;
        };
    }
}

#endif //SOKOBAN_CPP_WALL_HPP
