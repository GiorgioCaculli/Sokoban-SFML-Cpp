#include "main.hpp"

#include "ui/Menu.hpp"
#include "util/logger.hpp"

using namespace sokoban::ui;
using namespace sokoban::model;
using namespace sokoban::util;

int main( int argc, char *argv[] )
{
    Logger *logger = new Logger( "main" );
    remove( logger->get_file_name().c_str() );
    Menu *menu = new Menu();

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
