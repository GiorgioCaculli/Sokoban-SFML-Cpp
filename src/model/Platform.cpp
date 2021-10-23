#include "Platform.hpp"

#include <iostream>

using namespace sokoban::model;

const std::string platform_asset = "assets/images/PNG/EndPoint_Purple.png";

Platform::Platform( int x, int y )
        : Actor( x, y, platform_asset )
{
}

Platform::Platform( const Platform &platform )
        : Platform( platform.get_x(), platform.get_y() )
{
}

Platform &Platform::operator=( const Platform &platform )
{
    if( &platform != this )
    {
        set_x( platform.get_x() );
        set_y( platform.get_y() );
        set_asset( platform.get_asset() );
    }
    return *this;
}

Platform::~Platform()
{
    std::cout << "Deletion Platform -> x: " << get_x() << " - y: " << get_y() << std::endl;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Platform &platform )
{
    os << static_cast<const Actor &>(platform);
    return os;
}

Actor::ID Platform::get_type() const
{
    return Actor::PLATFORM;
}
