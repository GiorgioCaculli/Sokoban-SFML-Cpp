#include "Box.hpp"

#include <iostream>

using namespace sokoban::model;

const std::string box_asset = "assets/images/PNG/Crate_Brown.png";

Box::Box( int x, int y )
        : Movable( x, y, box_asset )
{

}
Box::Box( const Box &box )
        : Movable( box )
{

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
