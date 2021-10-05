#include "main.hpp"

#include "ui/menu.hpp"
#include "util/logger.hpp"
#include "model/Board.hpp"
#include "model/Box.hpp"
#include "model/Platform.hpp"
#include "model/Player.hpp"
#include "model/Wall.hpp"

#include <iostream>

using namespace sokoban::ui;
using namespace sokoban::model;
using namespace sokoban::util;

int main( int argc, char *argv[] )
{
    Logger *logger = new Logger( "main" );
    remove( logger->get_file_name().c_str() );
    Menu *menu = new Menu();

    Board *board = new Board();

    std::cout << *board << std::endl;

    delete board;

    int res = 0;

    try
    {
        res = menu->launch_application();
    } catch ( std::exception &e )
    {
        logger->log( LoggerLevel::FATAL, e.what() );
    }

    delete menu;
    delete logger;

    return res;
}
