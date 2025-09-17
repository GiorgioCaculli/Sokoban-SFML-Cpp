#ifndef SOKOBAN_STATE_IDENTIFIERS_HPP
#define SOKOBAN_STATE_IDENTIFIERS_HPP


namespace sokoban::ui::gui::States
{
    /**
     * ID of each state that characterizes it
     */
    enum class ID
    {
        None, /** No nature whatsoever */
        Title, /** The title screen */
        Menu, /** The menu screen */
        Game, /** The playable area */
        Pause, /** The pause screen */
        Settings, /** The settings screen */
    };
}


#endif //SOKOBAN_STATE_IDENTIFIERS_HPP
