#include "Wall.hpp"

#include <iostream>
#include <array>

using namespace sokoban::model;

const std::array< int, 4 > wall_round_grey_asset = { 0, 0, 64, 64 };

Wall::Wall( int x, int y )
        : Actor( x, y, wall_round_grey_asset )
{
}

Wall::Wall( const Wall &wall )
        : Wall( wall.get_x(), wall.get_y() )
{
}

Wall &Wall::operator=( const Wall &wall )
{
    if( &wall != this )
    {
        set_x( wall.get_x() );
        set_y( wall.get_y() );
        set_asset_coords( wall.get_asset_coords() );
    }
    return *this;
}

Wall::~Wall()
{
    std::cout << "Deletion Wall -> _x: " << get_x() << " - y: " << get_y() << std::endl;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Wall &wall )
{
    os << static_cast<const Actor &>(wall);
    return os;
}

Actor::ID Wall::get_type() const
{
    return Actor::WALL;
}
