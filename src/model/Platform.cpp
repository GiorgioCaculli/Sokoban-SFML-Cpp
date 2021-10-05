#include "Platform.hpp"

#include <iostream>

using namespace sokoban::model;

Platform::Platform( int x, int y )
        : Actor( x, y )
{

}
Platform::Platform( const Platform &platform )
        : Actor( platform )
{

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
