#ifndef SOKOBAN_SPRITE_NODE_HPP
#define SOKOBAN_SPRITE_NODE_HPP

#include "Scene_Node.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Sprite_Node
                    : public Scene_Node
            {
            public:
                explicit Sprite_Node( const sf::Texture &texture );
                Sprite_Node( sf::Texture &texture, const sf::IntRect &textureRect );
            private:
                sf::Sprite _sprite;
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
            };
        }
    }
}

#endif //SOKOBAN_SPRITE_NODE_HPP
