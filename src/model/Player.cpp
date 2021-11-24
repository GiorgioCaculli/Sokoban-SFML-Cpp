#include "Player.hpp"

#include <array>
#include <sstream>
#include <iostream>

using namespace sokoban::model;

const float OFFSET = 64;

std::array< float, 4 > character_facing_west = {
        0
        , 0
        , OFFSET
        , OFFSET
};
std::array< float, 4 > character_walking_west = {
        OFFSET * 1
        , 0
        , OFFSET
        , OFFSET
};

std::array< float, 4 > character_facing_east = {
        OFFSET * 2
        , 0
        , OFFSET
        , OFFSET
};
std::array< float, 4 > character_walking_east = {
        OFFSET * 3
        , 0
        , OFFSET
        , OFFSET
};

std::array< float, 4 > character_facing_south = {
        OFFSET * 4
        , 0
        , OFFSET
        , OFFSET
};

std::array< float, 4 > character_walking_south_right_step = {
        OFFSET * 5
        , 0
        , OFFSET
        , OFFSET
};
std::array< float, 4 > character_walking_south_left_step = {
        OFFSET * 6
        , 0
        , OFFSET
        , OFFSET
};

std::array< float, 4 > character_facing_north = {
        OFFSET * 7
        , 0
        , OFFSET
        , OFFSET
};
std::array< float, 4 > character_walking_north_right_step = {
        OFFSET * 8
        , 0
        , OFFSET
        , OFFSET
};
std::array< float, 4 > character_walking_north_left_step = {
        OFFSET * 9
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > player_asset_north = character_facing_north;
const std::array< float, 4 > player_asset_south = character_facing_south;
const std::array< float, 4 > player_asset_east = character_facing_east;
const std::array< float, 4 > player_asset_west = character_facing_west;

Player::Player( float x, float y )
        : Movable( x, y, player_asset_north )
{
    _player_face_map = std::map< Face, std::array< float, 4 > >
            {
                    {   Face::NORTH, player_asset_north }
                    , { Face::SOUTH, player_asset_south }
                    , { Face::EAST , player_asset_east }
                    , { Face::WEST , player_asset_west }
            };
}

Player::Player( const Player &player )
        : Player( player.get_x(), player.get_y() )
{
    set_asset_coords( player.get_asset_coords() );
    _player_face_map = player._player_face_map;
}

Player &Player::operator=( const Player &player )
{
    if ( &player != this )
    {
        set_x( player.get_x() );
        set_y( player.get_y() );
        set_asset_coords( player.get_asset_coords() );
        _player_face_map = player._player_face_map;
    }
    return *this;
}

Player::~Player()
{
    std::cout << "Deletion " << Player::to_string() << std::endl;
}

Actor::ID Player::get_type() const
{
    return Actor::PLAYER;
}

const std::map< Player::Face, std::array< float, 4 > > &Player::get_player_face_map() const
{
    return _player_face_map;
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
