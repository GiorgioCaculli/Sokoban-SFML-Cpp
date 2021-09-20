#include "main.hpp"

#include "ui/menu.hpp"
#include "util/logger.hpp"

#include <iostream>

using namespace sokoban::ui;
using namespace sokoban::util;

int main( int argc, char* argv[] )
{
    Logger *logger = new Logger( "main" );
    remove( logger->get_file_name().c_str());
    Menu* menu = new Menu();

    int res = menu->launch_application();

    delete menu;
    delete logger;

    return res;
}
