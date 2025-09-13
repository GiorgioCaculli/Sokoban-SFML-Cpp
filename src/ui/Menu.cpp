#include <ui/Menu.hpp>

#include <gui/Application.hpp>

#include <gzc/util/logger/Logger.hpp>

using namespace sokoban::ui;
using namespace sokoban::ui::gui;
using namespace gzc::util::logger;

Menu::Menu( const bool debugging )
    : _debugging( debugging )
{
    const Logger logger( "menu", "sokoban.log", true );
    try
    {
        logger.log( Logger::Level::INFO, "Init Main Frame" );
        if ( _debugging )
        {
            Application app( 1600, 900, "Sokoban Debug");
            _res = app.run();
        }
        else
        {
            Application main_frame;
            _res = main_frame.run();
        }
    } catch ( std::exception& e )
    {
        logger.log( Logger::Level::ERROR, e.what() );
        _res = -1;
    }
}

/**
 * Menu's constructor meant to initialize and execute the game.
 * Upon execution, a return code is entered.
 * Should any exception arise, the program's return code will be -1.
 */
Menu::Menu()
    : Menu( false )
{
}

/**
 * Menu's destructor
 */
Menu::~Menu()
= default;

/**
 * Function meant to return the games execution code
 * @return 0 if run correctly, -1 if not
 */
unsigned short Menu::launch_application() const
{
    return _res;
}
