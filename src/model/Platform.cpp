#include "Platform.hpp"

#include <sstream>
#include <iostream>

using namespace sokoban::model;

Platform::Platform( float x, float y )
        : Actor( x, y )
{
}

Platform::Platform( const Platform &platform )
        : Platform( platform.get_x(), platform.get_y() )
{
}

Platform &Platform::operator=( const Platform &platform )
{
    if ( &platform != this )
    {
        set_x( platform.get_x() );
        set_y( platform.get_y() );
    }
    return *this;
}

Platform::~Platform()
{
    std::cout << "Deletion " << Platform::to_string() << std::endl;
}

Actor::ID Platform::get_type() const
{
    return Actor::PLATFORM;
}

std::string Platform::to_string() const
{
    std::stringstream ss;
    ss << "Platform: " << Actor::to_string();
    return ss.str();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Platform &platform )
{
    os << platform.to_string();
    return os;
}
