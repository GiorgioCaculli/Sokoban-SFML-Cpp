#ifndef SOKOBAN_SPRITE_NODE_HPP
#define SOKOBAN_SPRITE_NODE_HPP

#include "scene_node.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class SpriteNode : public SceneNode
            {
            public:
                explicit SpriteNode( const sf::Texture &texture );

                SpriteNode( const sf::Texture &texture, const sf::IntRect &textureRect );

            private:
                sf::Sprite sprite;
            private:
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
            };
        }
    }
}

#endif //SOKOBAN_SPRITE_NODE_HPP
