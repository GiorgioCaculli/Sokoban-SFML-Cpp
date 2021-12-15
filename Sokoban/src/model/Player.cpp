#include "Player.hpp"

#include "../util/Logger.hpp"

#include <sstream>
#include <iostream>

using namespace sokoban::model;
using namespace sokoban::util;

/**
 * Default constructor for the player
 * @param x The X coordinates on the board
 * @param y The Y coordinates on the board
 */
Player::Player( float x, float y )
        : Movable( x, y )
{
}

/**
 * Copy constructor for the player
 * @param player The player we wish to copy the information from
 */
Player::Player( const Player &player )
        : Player( player.get_x(), player.get_y() )
{
}

/**
 * Redefinition of the = operator
 * @param player The player we wish to copy the information from
 * @return The new instance of a player with the copied information
 */
Player &Player::operator=( const Player &player )
{
    if ( &player != this )
    {
        set_x( player.get_x() );
        set_y( player.get_y() );
    }
    return *this;
}

/**
 * Default destructor for the player
 */
Player::~Player()
{
    Logger::log( LoggerLevel::INFO, "Deletion " + Player::to_string() );
}

/**
 * Getter used to retrieve a player actor's nature
 * @return The fact that the actor is a player
 */
Actor::ID Player::get_type() const
{
    return Actor::PLAYER;
}

/**
 * Textual output containing the Player's information
 * @return Text with the player's info
 */
std::string Player::to_string() const
{
    std::stringstream ss;
    ss << "Player: " << Movable::to_string();
    return ss.str();
}
