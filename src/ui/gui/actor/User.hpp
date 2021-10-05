#ifndef SOKOBAN_USER_HPP
#define SOKOBAN_USER_HPP

#include "entity.hpp"
#include "../resource_identifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class User
                    : public Entity
            {
            public:
                enum Face
                {
                    Player_North,
                    Player_South,
                    Player_East,
                    Player_West
                };
                User( Face face, const TextureHolder &textures );
            private:
                Face face;
                sf::Sprite sprite;
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
            };
        }
    }
}

#endif //SOKOBAN_USER_HPP
