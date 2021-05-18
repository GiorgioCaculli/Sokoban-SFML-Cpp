#include "actor.hpp"

#include "../util/logger.hpp"

#include <iostream>

using namespace sokoban::core;
using namespace sokoban::util;

Actor::Actor( int x, int y )
{
    logger = new Logger( "Player" );
    setX( x );
    setY( y );
}

Actor::~Actor()
{
    logger->log( LoggerLevel::INFO, "Player Destruction" );
};

void Actor::setX( int x )
{
    this->_x = x;
}

int Actor::getX() const
{
    return _x;
}

void Actor::setY( int y )
{
    this->_y = y;
}

int Actor::getY() const
{
    return _y;
}

bool Actor::is_left_collision( Actor *actor ) const
{
    return getX() - SPACE == actor->getX() && getY() == actor->getY();
}

bool Actor::is_right_collision( Actor *actor ) const
{
    return getX() + SPACE == actor->getX() && getY() == actor->getY();
}

bool Actor::is_top_collision( Actor *actor ) const
{
    return getY() - SPACE == actor->getY() && getX() == actor->getX();
}

bool Actor::is_bottom_collision( Actor *actor ) const
{
    return getY() + SPACE == actor->getY() && getX() == actor->getX();
}
