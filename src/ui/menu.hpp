#ifndef SOKOBAN_MENU_HPP
#define SOKOBAN_MENU_HPP

#include "gui/main_frame.hpp"

namespace sokoban
{
    namespace ui
    {
        class Menu
        {
        public:
            Menu();

            virtual ~Menu();

            int launch_application() const;

        private:
            gui::MainFrame *main_frame;
        };
    }
}


#endif //SOKOBAN_MENU_HPP
