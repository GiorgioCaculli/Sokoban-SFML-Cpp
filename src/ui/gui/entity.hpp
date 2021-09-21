#ifndef SOKOBAN_ENTITY_HPP
#define SOKOBAN_ENTITY_HPP

#include "scene_node.hpp"

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Entity
            {
            public:
                void set_velocity( sf::Vector2f velocity );

                void set_velocity( float vx, float vy );

                sf::Vector2f get_velocity() const;

            private:
                sf::Vector2f velocity;
            private:
                virtual void update_current( sf::Time dt );
            };
        }
    }
}

#endif //SOKOBAN_ENTITY_HPP
