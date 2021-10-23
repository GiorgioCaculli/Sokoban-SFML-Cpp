#include "Sprite_Node.hpp"

#include <sstream>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

SpriteNode::SpriteNode( sf::Texture &texture, const sf::IntRect &textureRect )
{
    sprite = new sf::Sprite();
    sprite->setTexture( texture );
    sprite->setTextureRect( textureRect );
    std::stringstream ss;
    ss << "SpriteNode init";
    ss << " X: " << this->getPosition().x;
    ss << " Y: " << this->getPosition().y;
    Logger::log( LoggerLevel::DEBUG, ss.str() );
}

SpriteNode::SpriteNode( sf::Texture &texture )
{
    sprite = new sf::Sprite();
    sprite->setTexture( texture );
    std::stringstream ss;
    ss << "SpriteNode init";
    ss << " X: " << this->getPosition().x;
    ss << " Y: " << this->getPosition().y;
    Logger::log( LoggerLevel::DEBUG, ss.str() );
}

void SpriteNode::draw_current( sf::RenderTarget &target, sf::RenderStates states ) const
{
    target.draw( *sprite, states );
}

void SpriteNode::set_texture( sf::Texture &texture )
{
    sprite->setTexture( texture );
}

SpriteNode::~SpriteNode()
{
    delete sprite;
}
