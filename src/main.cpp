#include <ui/Menu.hpp>
#include <gzc/util/logger/Logger.hpp>

#include <iostream>
#include <vector>

using namespace sokoban::ui;
using namespace gzc::util::logger;

/**
 * Main function that initializes the game's logger.
 * The logger will log everything inside a file called sokoban.log
 * File which is instantiated upon execution of the program.
 * Once the logger is initialized, we initialize the menu
 * which will be used to start the application.
 * If no exception is caught, the program will return 0, otherwise -1.
 */
int main( const int argc, char* argv[ ] )
{
    bool debugging = false;
    std::cout << "Calling: ";
    std::vector< std::string > args( argc );

    for ( int i = 0; i < argc; i++ )
    {
        std::cout << argv[ i ] << " ";
        args[ i ] = argv[ i ];
        if ( args[ i ].find( "--debug" ) != std::string::npos || args[ i ].find( "-d" ) != std::string::npos )
        {
            debugging = true;
        }
    }

    std::cout << std::endl;

    const Logger logger( "main", "sokoban.log", true );
    remove( logger.get_file_name().c_str() );

    logger.log( Logger::Level::INFO, "Starting Menu..." );

    int res = 0;

    if ( debugging )
    {
        const Menu menu( true );
        logger.log( Logger::Level::INFO, "Running Game in debug mode" );

        res = menu.launch_application();
    } else
    {
        const Menu menu;
        logger.log( Logger::Level::INFO, "Running Game..." );

        res = menu.launch_application();
    }

    logger.log( Logger::Level::INFO, "Closing Sokoban..." );

    return res;
}
