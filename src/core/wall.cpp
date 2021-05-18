#include "wall.hpp"
#include "../util/logger.hpp"

using namespace sokoban::core;
using namespace sokoban::util;

Wall::Wall( int x, int y )
        : Actor( x, y )
{
    init_wall();
}

Wall::~Wall()
{
}

void Wall::init_wall()
{

}
