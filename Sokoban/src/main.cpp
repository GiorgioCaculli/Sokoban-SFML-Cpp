#include <gzc/games/sokoban/ui/Menu.hpp>
#include <gzc/logger/Logger.hpp>

#include <iostream>

using namespace sokoban::ui;
using namespace util;

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
    std::cout << "Calling: ";

    for( int i = 0; i < argc; i++ )
    {
        std::cout << argv[i] << " ";
    }

    std::cout << std::endl;

    Logger logger( "main", "sokoban.log", true );
    remove( logger.get_file_name().c_str() );

    logger.log( Logger::Level::INFO, "Starting Menu..." );

    Menu menu;

    logger.log( Logger::Level::INFO, "Running Game..." );

    int res = menu.launch_application();

    logger.log( Logger::Level::INFO, "Closing Sokoban..." );

    return res;
}
