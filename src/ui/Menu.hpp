#ifndef SOKOBAN_MENU_HPP
#define SOKOBAN_MENU_HPP

#include "gui/Main_Window.hpp"
#include "../util/logger.hpp"

namespace sokoban
{
    namespace ui
    {
        using namespace sokoban::ui::gui;
        using namespace sokoban::util;

        class Menu
        {
        public:
            Menu();
            virtual ~Menu();
            unsigned short launch_application() const;
        private:
            MainFrame *main_frame;
            Logger *logger {};
        };
    }
}

#endif //SOKOBAN_MENU_HPP
