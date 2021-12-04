#include "Entity_Player.hpp"

using namespace sokoban::ui::gui::entity;

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

Entity_Player::Entity_Player( float x, float y )
        : model::Player( x, y )
        , Entity_Movable( player_asset_south )
{
    _player_face_map = std::map< Face, std::array< float, 4 > >
            {
                    {   Face::NORTH, player_asset_north }
                    , { Face::SOUTH, player_asset_south }
                    , { Face::EAST , player_asset_east }
                    , { Face::WEST , player_asset_west }
            };
}

Entity_Player::Entity_Player( const Entity_Player &entity )
: Entity_Player( entity.get_x(), entity.get_y() )
{
    set_asset_coords( entity.get_asset_coords() );
    _player_face_map = entity._player_face_map;
}

Entity_Player &Entity_Player::operator=( const Entity_Player &entity )
{
    if( &entity != this )
    {
        model::Player::operator=( entity );
        Entity::operator=( entity );
        set_asset_coords( entity.get_asset_coords() );
        _player_face_map = entity._player_face_map;
    }
    return *this;
}

Entity_Player::~Entity_Player()
{
    model::Player::~Player();
}

std::string Entity_Player::to_string() const
{
    return Player::to_string();
}

const std::map< Entity_Player::Face, std::array< float, 4>> &Entity_Player::get_player_face_map() const
{
    return _player_face_map;
}

std::ostream &sokoban::ui::gui::entity::operator<<( std::ostream &os, const Entity_Player &entity )
{
    os << entity.to_string();
    return os;
}
