#ifndef SOKOBAN_MENU_HPP
#define SOKOBAN_MENU_HPP

namespace sokoban
{
    namespace ui
    {
        class Menu
        {
        public:
            Menu();
            ~Menu();
            unsigned short launch_application() const;
        private:
            int _res;
        };
    }
}

#endif //SOKOBAN_MENU_HPP
