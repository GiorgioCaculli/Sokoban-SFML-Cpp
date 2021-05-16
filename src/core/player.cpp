#include "player.hpp"

using namespace sokoban::core;

Player::Player( int x, int y )
        : Actor( x, y )
{
    init_player();
}

void Player::init_player()
{

}

void Player::move( int x, int y )
{
    setX( getX() + x );
    setY( getY() + y );
}

Player::~Player()
= default;
