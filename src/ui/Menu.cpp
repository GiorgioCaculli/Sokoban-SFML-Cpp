#include "Menu.hpp"

#include "../util/Logger.hpp"

using namespace sokoban::ui;
using namespace sokoban::ui::gui;
using namespace sokoban::util;

Menu::Menu()
{
    Logger::log( LoggerLevel::INFO, "Init Menu" );

    Logger::log( LoggerLevel::INFO, "Init Main Frame" );
    MainWindow main_frame;
    _res = main_frame.run();
}

Menu::~Menu()
= default;

unsigned short Menu::launch_application() const
{
    return _res;
}
