#include "Box.hpp"

#include <iostream>

using namespace sokoban::model;

const std::string box_asset = "assets/images/PNG/Crate_Brown.png";

Box::Box( int x, int y )
        : Movable( x, y, box_asset )
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
        set_asset( box.get_asset() );
    }
    return *this;
}

Box::~Box()
{
    std::cout << "Deletion Box -> x: " << get_x() << " - y: " << get_y() << std::endl;
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
