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
        break;
    case SOUTH:
        set_asset( player_asset_south );
        break;
    case EAST:
        set_asset( player_asset_east );
        break;
    case WEST:
        set_asset( player_asset_west );
        break;
    default:
        set_asset( player_asset_south );
        break;
    }
}
