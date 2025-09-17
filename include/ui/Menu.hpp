#ifndef SOKOBAN_MENU_HPP
#define SOKOBAN_MENU_HPP

namespace sokoban::ui
{
    class Menu
    {
    public:
        explicit Menu( bool debugging );

        Menu();

        ~Menu();

        [[nodiscard]] unsigned short launch_application() const;

    private:
        int _res; /** The end result for the game's execution */
        bool _debugging;
    };
}


#endif //SOKOBAN_MENU_HPP
