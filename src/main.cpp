#include "main.hpp"

#include "ui/Menu.hpp"
#include "util/Logger.hpp"

using namespace sokoban::ui;
using namespace sokoban::util;

/**
 * Main function that initializes the game's logger.
 * The logger will log everything inside a file called sokoban.log
 * File which is instantiated upon execution of the program.
 * Once the logger is initialized, we initialize the menu
 * which will be used to start the application.
 * If no exception is caught, the program will return 0, otherwise -1.
 */
int main( int argc, char *argv[] )
{
    Logger logger( "sokoban.log" );
    remove( logger.get_file_name().c_str() );

    Logger::log( LoggerLevel::INFO, "Starting Menu..." );

    Menu menu;

    Logger::log( LoggerLevel::INFO, "Running Game..." );

    int res = menu.launch_application();

    Logger::log( LoggerLevel::INFO, "Closing Sokoban..." );

    return res;
}
