#include "platform.hpp"

using namespace sokoban::core;

Platform::Platform( int x, int y )
        : Actor( x, y )
{
    init_platform();
}

Platform::~Platform()
= default;

void Platform::init_platform()
{

}
