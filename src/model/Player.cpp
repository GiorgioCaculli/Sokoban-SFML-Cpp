#include "Player.hpp"

#include <iostream>

using namespace sokoban::model;

const std::string player_asset_north = "assets/images/PNG/Character7.png";
const std::string player_asset_south = "assets/images/PNG/Character4.png";
const std::string player_asset_east = "assets/images/PNG/Character2.png";
const std::string player_asset_west = "assets/images/PNG/Character1.png";

Player::Player( int x, int y )
        : Movable( x, y, player_asset_north )
{
}

Player::Player( const Player &player )
        : Player( player.get_x(), player.get_y() )
{
}

Player &Player::operator=( const Player &player )
{
    if( &player != this )
    {
        set_x( player.get_x() );
        set_y( player.get_y() );
        set_asset( player.get_asset() );
        current_face = player.current_face;
    }
    return *this;
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

Actor::ID Player::get_type() const
{
    return Actor::PLAYER;
}

void Player::set_face( const Face &face )
{
    switch ( face )
    {
    case NORTH:
        set_asset( player_asset_north );
        current_face = NORTH;
        break;
    case SOUTH:
        set_asset( player_asset_south );
        current_face = SOUTH;
        break;
    case EAST:
        set_asset( player_asset_east );
        current_face = EAST;
        break;
    case WEST:
        set_asset( player_asset_west );
        current_face = WEST;
        break;
    default:
        set_asset( player_asset_south );
        current_face = SOUTH;
        break;
    }
}

Player::Face Player::get_face() const
{
    return current_face;
}
