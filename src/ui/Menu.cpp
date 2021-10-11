#include "Menu.hpp"

#include "../util/Logger.hpp"

using namespace sokoban::ui;
using namespace sokoban::ui::gui;
using namespace sokoban::util;

Menu::Menu()
{
    Logger::log( LoggerLevel::INFO, "Init Menu" );

    Logger::log( LoggerLevel::INFO, "Init Main Frame" );
    main_frame = new MainFrame();
}

Menu::~Menu()
{
    delete main_frame;
}

unsigned short Menu::launch_application() const
{
    return main_frame->run();
}
