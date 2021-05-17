#include "menu.hpp"

using namespace sokoban::ui;
using namespace sokoban::ui::gui;

Menu::Menu()
{
    main_frame = new MainFrame();
}

Menu::~Menu()
{
    delete main_frame;
}

int Menu::launch_application() const
{
    return main_frame->glfw_result_code();
}
