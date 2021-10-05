#include "Wall.hpp"

#include <iostream>

using namespace sokoban::model;

Wall::Wall( int x, int y )
        : Actor( x, y )
{

}
Wall::Wall( const Wall &wall )
        : Actor( wall )
{

}
Wall::~Wall()
{
    std::cout << "Deletion Wall -> x: " << get_x() << " - y: " << get_y() << std::endl;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Wall &wall )
{
    os << static_cast<const Actor &>(wall);
    return os;
}
