#include "Menu.hpp"
#include "../util/logger.hpp"

using namespace sokoban::ui;
using namespace sokoban::ui::gui;
using namespace sokoban::util;

Menu::Menu()
{
    logger = new Logger( "menu" );
    logger->log( LoggerLevel::INFO, "Init Menu" );

    logger->log( LoggerLevel::INFO, "Init Main Frame" );
    main_frame = new MainFrame();
}

Menu::~Menu()
{
    delete main_frame;
    delete logger;
}

unsigned short Menu::launch_application() const
{
    return main_frame->run();
}
