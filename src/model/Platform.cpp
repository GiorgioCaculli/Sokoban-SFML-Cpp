#include "Platform.hpp"

#include <iostream>
#include <array>

using namespace sokoban::model;

const std::array< int, 4 > platform_purple_asset = { 0, 384, 32, 32  };

Platform::Platform( int x, int y )
        : Actor( x, y, platform_purple_asset )
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
        set_asset_coords( platform.get_asset_coords() );
    }
    return *this;
}

Platform::~Platform()
{
    std::cout << "Deletion Platform -> _x: " << get_x() << " - y: " << get_y() << std::endl;
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
