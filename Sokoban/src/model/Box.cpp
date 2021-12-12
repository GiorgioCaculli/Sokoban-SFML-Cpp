#include "Box.hpp"

#include "../util/Logger.hpp"

#include <sstream>
#include <iostream>

using namespace sokoban::model;
using namespace sokoban::util;

Box::Box( float x, float y )
        : Movable( x, y )
{
}

Box::Box( const Box &box )
        : Box( box.get_x(), box.get_y() )
{
}

Box &Box::operator=( const Box &box )
{
    if ( &box != this )
    {
        set_x( box.get_x() );
        set_y( box.get_y() );
    }
    return *this;
}

Box::~Box()
{
    Logger::log( LoggerLevel::INFO, "Deletion " + Box::to_string() );
}

Actor::ID Box::get_type() const
{
    return Actor::BOX;
}

std::string Box::to_string() const
{
    std::stringstream ss;
    ss << "Box: " << Movable::to_string();
    return ss.str();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Box &box )
{
    os << box.to_string();
    return os;
}
