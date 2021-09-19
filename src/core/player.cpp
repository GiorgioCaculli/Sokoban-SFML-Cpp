#include "player.hpp"

#include <iostream>

using namespace sokoban::core;

Player::Player( int x, int y )
        :Actor( x, y )
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
{
    std::cout << "Player deletion" << std::endl;
};
