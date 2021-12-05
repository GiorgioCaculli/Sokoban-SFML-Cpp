#include "main.hpp"

#include "ui/Menu.hpp"
#include "util/Logger.hpp"

using namespace sokoban::ui;
using namespace sokoban::util;

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
