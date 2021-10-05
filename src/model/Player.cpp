#include "Player.hpp"

#include <iostream>

using namespace sokoban::model;

Player::Player( int x, int y )
        : Movable( x, y )
{

}
Player::Player( const Player &player )
        : Movable( player )
{

}
Player::~Player()
{
    std::cout << "Deletion Player -> x: " << get_x() << " - y: " << get_y() << std::endl;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Player &player )
{
    os << static_cast<const Movable &>(player);
    return os;
}
