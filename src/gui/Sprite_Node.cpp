#include <gui/Sprite_Node.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the sprite node
 * @param texture The texture to display the sprite with
 */
Sprite_Node::Sprite_Node( const sf::Texture& texture )
    : _sprite( texture )
{
}

/**
 * Default constructor for the sprite node
 * @param texture The texture to display the sprite with
 * @param textureRect The coordinates of a texture within a sprite sheet
 */
Sprite_Node::Sprite_Node( const sf::Texture& texture, const sf::IntRect& textureRect )
    : _sprite( texture, textureRect )
{
}

/**
 * Setter for the sprite's texture
 * @param texture The new texture to display
 */
void Sprite_Node::set_texture( const sf::Texture& texture )
{
    _sprite.setTexture( texture );
}

/**
 * Setter for the sprite's texture
 * @param texture The new texture to display
 * @param textureRect The coordinates of the texture within a sprite sheet
 */
void Sprite_Node::set_texture( const sf::Texture& texture, const sf::IntRect& textureRect )
{
    set_texture( texture );
    _sprite.setTextureRect( textureRect );
}

/**
 * Visually display the sprite node
 * @param target The target to display the sprite onto
 * @param states The various states that characterize the window
 */
void Sprite_Node::draw_current( sf::RenderTarget& target, const sf::RenderStates& states ) const
{
    target.draw( _sprite, states );
}
