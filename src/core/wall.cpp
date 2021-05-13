#include "wall.hpp"

using namespace com::masticass::sokoban::core;

Wall::Wall( int x, int y )
        : Actor( x, y )
{
    init_wall();
}

Wall::~Wall()
= default;

void Wall::init_wall()
{

}
