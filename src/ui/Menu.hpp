#ifndef SOKOBAN_MENU_HPP
#define SOKOBAN_MENU_HPP

#include "gui/Main_Window.hpp"

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
            int res;
        };
    }
}

#endif //SOKOBAN_MENU_HPP
