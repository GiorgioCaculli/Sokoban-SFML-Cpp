#include "main.hpp"

#include <iostream>

using namespace com::masticass::sokoban::core;

int main( int argc, char *argv[] )
{
    std::cout << "Hello, World!" << std::endl;

    Actor *p = new Player( 10, -5 );

    std::cout << "X: " << p->getX() << " Y: " << p->getY() << std::endl;
    return 0;
}
