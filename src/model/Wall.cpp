#include "Wall.hpp"

#include <array>
#include <sstream>
#include <iostream>

using namespace sokoban::model;

const std::array< float, 4 > wall_round_grey_asset = { 0, 0, 64, 64 };

Wall::Wall( float x, float y )
        : Actor( x, y, wall_round_grey_asset )
{
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
