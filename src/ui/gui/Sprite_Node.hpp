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
                sf::Sprite sprite;
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
            public:
                explicit SpriteNode( const sf::Texture &texture );
                SpriteNode( const sf::Texture &texture, const sf::IntRect &textureRect );
                virtual ~SpriteNode();
            };
        }
    }
}

#endif //SOKOBAN_SPRITE_NODE_HPP
