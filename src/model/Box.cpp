#include "Box.hpp"

#include <iostream>

using namespace sokoban::model;

Box::Box( int x, int y )
        : Movable( x, y )
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
