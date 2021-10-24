#include "Player.hpp"

#include <iostream>
#include <array>

using namespace sokoban::model;

std::array< int, 4 > character_facing_north = { 384, 0, 37, 60 };

std::array< int, 4 > character_walking_right = { 320, 128, 42, 58 };
std::array< int, 4 > character_walking_north_left_step = {
        character_walking_right[ 0 ] + character_walking_right[ 2 ],
        character_walking_right[ 1 ],
        37, 60 };

std::array< int, 4 > character_facing_east = {
        character_walking_right[ 0 ],
        character_walking_right[ 1 ] + character_walking_right[ 3 ],
        42, 59 };
std::array< int, 4 > character_walking_north_right_step = {
        character_facing_east[ 0 ] + character_facing_east[ 2 ],
        character_facing_east[ 1 ],
        37, 60 };

std::array< int, 4 > character_facing_west = {
        character_facing_east[ 0 ],
        character_facing_east[ 1 ] + character_facing_east[ 3 ],
        42, 59 };
std::array< int, 4 > character_facing_south = {
        character_facing_west[ 0 ] + character_facing_west[ 2 ],
        character_facing_west[ 1 ] + 3,
        37, 59 };

std::array< int, 4 > character_walking_left = {
        character_facing_west[ 0 ],
        character_facing_west[ 1 ] + character_facing_west[ 3 ],
        42, 58 };

std::array< int, 4 > character_walking_south_right_step = {
        character_walking_left[ 0 ],
        character_walking_left[ 1 ] + character_walking_left[ 3 ],
        37, 59 };
std::array< int, 4 > character_walking_south_left_step = {
        character_walking_south_right_step[ 0 ] + character_walking_south_right_step[ 2 ],
        character_walking_south_right_step[ 1 ],
        37, 59 };

const std::array< int, 4 > player_asset_north = character_facing_north;
const std::array< int, 4 > player_asset_south = character_facing_south;
const std::array< int, 4 > player_asset_east = character_facing_east;
const std::array< int, 4 > player_asset_west = character_facing_west;

Player::Player( int x, int y )
        : Movable( x, y, player_asset_north )
        , _current_face( Face::NORTH )
{
    _animations = {
            character_facing_north,
            character_walking_north_right_step,
            character_walking_north_left_step,
            character_facing_west,
            character_walking_right,
            character_facing_south,
            character_walking_south_right_step,
            character_walking_south_left_step,
            character_facing_east,
            character_walking_left
    };
}

Player::Player( const Player &player )
        : Player( player.get_x(), player.get_y() )
{
    set_asset_coords( player.get_asset_coords() );
    _current_face = player._current_face;
    _animations = player._animations;
}

Player &Player::operator=( const Player &player )
{
    if( &player != this )
    {
        set_x( player.get_x() );
        set_y( player.get_y() );
        set_asset_coords( player.get_asset_coords() );
        _current_face = player._current_face;
        _animations = player._animations;
    }
    return *this;
}

Player::~Player()
{
    std::cout << "Deletion Player -> _x: " << get_x() << " - y: " << get_y() << std::endl;
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
        set_asset_coords( player_asset_north );
        _current_face = NORTH;
        break;
    case SOUTH:
        set_asset_coords( player_asset_south );
        _current_face = SOUTH;
        break;
    case EAST:
        set_asset_coords( player_asset_east );
        _current_face = EAST;
        break;
    case WEST:
        set_asset_coords( player_asset_west );
        _current_face = WEST;
        break;
    default:
        set_asset_coords( player_asset_south );
        _current_face = SOUTH;
        break;
    }
}

Player::Face Player::get_face() const
{
    return _current_face;
}

std::array< std::array< int, 4 >, 10 > Player::get_animations() const
{
    return _animations;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Player &player )
{
    os << static_cast<const Movable &>(player);
    return os;
}
