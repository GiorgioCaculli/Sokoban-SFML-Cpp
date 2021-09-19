#include "actor.hpp"

#include "../util/logger.hpp"

#include <iostream>

using namespace sokoban::core;
using namespace sokoban::util;

Actor::Actor( float x, float y )
{
    logger = new Logger( "Player" );
    setX( x );
    setY( y );

    sprite = new sf::Sprite();
    sprite->setPosition( x, y );
}

Actor::~Actor()
= default;

sf::Sprite Actor::get_texture()
{
    return *sprite;
}

void Actor::set_texture( sf::Texture *texture )
{
    sprite->setTexture( *texture );
}

void Actor::setX( float x )
{
    this->_x = x;
}

float Actor::getX() const
{
    return _x;
}

void Actor::setY( float y )
{
    this->_y = y;
}

float Actor::getY() const
{
    return _y;
}

bool Actor::is_left_collision( Actor* actor ) const
{
    return getX() - SPACE == actor->getX() && getY() == actor->getY();
}

bool Actor::is_right_collision( Actor* actor ) const
{
    return getX() + SPACE == actor->getX() && getY() == actor->getY();
}

bool Actor::is_top_collision( Actor* actor ) const
{
    return getY() - SPACE == actor->getY() && getX() == actor->getX();
}

bool Actor::is_bottom_collision( Actor* actor ) const
{
    return getY() + SPACE == actor->getY() && getX() == actor->getX();
}
