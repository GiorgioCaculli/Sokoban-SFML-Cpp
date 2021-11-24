#include "Wall.hpp"

#include <array>
#include <sstream>
#include <iostream>

using namespace sokoban::model;

const float OFFSET = 64;

const std::array< float, 4 > wall_round_beige_asset = {
        0
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > wall_round_black_asset = {
        OFFSET * 1
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > wall_round_brown_asset = {
        OFFSET * 2
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > wall_round_white_asset = {
        OFFSET * 3
        , 0
        , OFFSET
        , OFFSET
};

Wall::Wall( float x, float y )
        : Actor( x, y, wall_round_white_asset )
{
    _wall_color_map = std::map< Color, std::array< float, 4 > >
            {
                    {   Color::BEIGE, wall_round_beige_asset }
                    , { Color::BLACK, wall_round_black_asset }
                    , { Color::BROWN, wall_round_brown_asset }
                    , { Color::WHITE, wall_round_white_asset }
            };
}

Wall::Wall( const Wall &wall )
        : Wall( wall.get_x(), wall.get_y() )
{
}

Wall &Wall::operator=( const Wall &wall )
{
    if ( &wall != this )
    {
        set_x( wall.get_x() );
        set_y( wall.get_y() );
        set_asset_coords( wall.get_asset_coords() );
    }
    return *this;
}

Wall::~Wall()
{
    std::cout << "Deletion " << Wall::to_string() << std::endl;
}

Actor::ID Wall::get_type() const
{
    return Actor::WALL;
}

const std::map< Wall::Color, std::array< float, 4 > > &Wall::get_wall_color_map() const
{
    return _wall_color_map;
}

std::string Wall::to_string() const
{
    std::stringstream ss;
    ss << "Wall: " << Actor::to_string();
    return ss.str();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Wall &wall )
{
    os << wall.to_string();
    return os;
}
