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
            class SpriteNode
                    : public SceneNode
            {
            private:
                sf::Sprite *sprite;
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
            public:
                explicit SpriteNode( sf::Texture &texture );
                SpriteNode(sf::Texture &texture, const sf::IntRect &textureRect );
                virtual ~SpriteNode();
                void set_texture( sf::Texture &texture );
            };
        }
    }
}

#endif //SOKOBAN_SPRITE_NODE_HPP
