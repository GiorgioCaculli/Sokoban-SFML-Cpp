#include "Sprite_Node.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

SpriteNode::SpriteNode( const sf::Texture &texture, const sf::IntRect &textureRect )
        : sprite( texture, textureRect )
{

}

SpriteNode::SpriteNode( const sf::Texture &texture )
        : sprite( texture )
{

}

void SpriteNode::draw_current( sf::RenderTarget &target, sf::RenderStates states ) const
{
    target.draw( sprite, states );
}

SpriteNode::~SpriteNode()
= default;
