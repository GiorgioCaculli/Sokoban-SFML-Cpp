#include "Player.hpp"

#include "../util/Logger.hpp"

#include <sstream>
#include <iostream>

using namespace sokoban::model;
using namespace sokoban::util;

Player::Player( float x, float y )
        : Movable( x, y )
{
}

Player::Player( const Player &player )
        : Player( player.get_x(), player.get_y() )
{
}

Player &Player::operator=( const Player &player )
{
    if ( &player != this )
    {
        set_x( player.get_x() );
        set_y( player.get_y() );
    }
    return *this;
}

Player::~Player()
{
    Logger::log( LoggerLevel::INFO, "Deletion " + Player::to_string() );
}

Actor::ID Player::get_type() const
{
    return Actor::PLAYER;
}

std::string Player::to_string() const
{
    std::stringstream ss;
    ss << "Player: " << Movable::to_string();
    return ss.str();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Player &player )
{
    os << player.to_string();
    return os;
}
