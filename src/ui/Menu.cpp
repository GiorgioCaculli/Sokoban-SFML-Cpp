#include "Menu.hpp"

#include "gui/Application.hpp"

using namespace sokoban::ui;
using namespace sokoban::ui::gui;
using namespace sokoban::util;

/**
 * Menu's constructor meant to initialize and execute the game.
 * Upon execution, a return code is entered.
 * Should any exception arise, the program's return code will be -1.
 */
Menu::Menu()
{
    try
    {
        Logger::log( LoggerLevel::INFO, "Init Main Frame" );
        Application main_frame;
        _res = main_frame.run();
    }
    catch ( std::exception &e )
    {
        Logger::log( LoggerLevel::ERROR, e.what() );
        _res = -1;
    }
}

Menu::~Menu()
= default;

unsigned short Menu::launch_application() const
{
    return _res;
}
