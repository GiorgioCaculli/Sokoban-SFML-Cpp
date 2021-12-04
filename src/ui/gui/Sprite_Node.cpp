#include "Sprite_Node.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

Sprite_Node::Sprite_Node( const sf::Texture &texture )
        : _sprite( texture )
{
}

Sprite_Node::Sprite_Node( const sf::Texture &texture, const sf::IntRect &textureRect )
        : _sprite( texture, textureRect )
{

}

void Sprite_Node::set_texture( const sf::Texture &texture )
{
    _sprite.setTexture( texture );
}
void Sprite_Node::set_texture( const sf::Texture &texture, const sf::IntRect &textureRect )
{
    set_texture( texture );
    _sprite.setTextureRect( textureRect );
}

void Sprite_Node::draw_current( sf::RenderTarget &target, sf::RenderStates states ) const
{
    target.draw( _sprite, states );
}
