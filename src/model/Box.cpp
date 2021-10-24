#include "Box.hpp"

#include <iostream>
#include <array>

using namespace sokoban::model;

const std::array< int, 4 > box_brown_light_asset = { 192, 256, 64, 64 };

Box::Box( int x, int y )
        : Movable( x, y, box_brown_light_asset )
{
}

Box::Box( const Box &box )
        : Box( box.get_x(), box.get_y() )
{
}

Box &Box::operator=( const Box &box )
{
    if( &box != this )
    {
        set_x( box.get_x() );
        set_y( box.get_y() );
        set_asset_coords( box.get_asset_coords() );
    }
    return *this;
}

Box::~Box()
{
    std::cout << "Deletion Box -> _x: " << get_x() << " - y: " << get_y() << std::endl;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Box &box )
{
    os << static_cast<const Movable &>(box);
    return os;
}

Actor::ID Box::get_type() const
{
    return Actor::BOX;
}
