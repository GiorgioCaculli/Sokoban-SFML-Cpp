#include "main.hpp"

#include "ui/Menu.hpp"
#include "util/Logger.hpp"

using namespace sokoban::ui;
using namespace sokoban::model;
using namespace sokoban::util;

int main( int argc, char *argv[] )
{
    Logger logger( "main" );
    remove( logger.get_file_name().c_str() );

    Logger::log( LoggerLevel::INFO, "Starting menu..." );

    Menu *menu = new Menu();

    int res = 0;

    Logger::log( LoggerLevel::INFO, "Running game..." );

    try
    {
        res = menu->launch_application();
    } catch ( std::exception &e )
    {
        Logger::log( LoggerLevel::FATAL, e.what() );
    }

    delete menu;

    Logger::log( LoggerLevel::INFO, "Closing Sokoban..." );
    return res;
}
