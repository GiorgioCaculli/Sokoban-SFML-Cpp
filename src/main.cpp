#include "main.hpp"

#include <iostream>

using namespace sokoban::core;
using namespace sokoban::ui;

int main( int argc, char *argv[] )
{
    std::cout << "Hello, World!" << std::endl;

    Actor *p = new Player( 10, -5 );

    std::cout << "X: " << p->getX() << " Y: " << p->getY() << std::endl;

    Menu *menu = new Menu();
    return menu->launch_application();
}
