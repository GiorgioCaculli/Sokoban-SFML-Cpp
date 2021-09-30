#ifndef SOKOBAN_PLAYER_HPP
#define SOKOBAN_PLAYER_HPP

#include "entity.hpp"
#include "resource_identifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Player : public Entity
            {
            public:
                enum Face
                {
                    North,
                    South,
                    East,
                    West
                };
            public:
                Player( Face face, const TextureHolder &textures );

            private:
                Face face;
                sf::Sprite sprite;
            private:
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
            };
        }
    }
}

#endif //SOKOBAN_PLAYER_HPP
