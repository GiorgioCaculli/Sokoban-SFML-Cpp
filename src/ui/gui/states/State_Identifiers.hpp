#ifndef SOKOBAN_STATE_IDENTIFIERS_HPP
#define SOKOBAN_STATE_IDENTIFIERS_HPP

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            namespace States
            {
                /**
                 * ID of each state that characterizes it
                 */
                enum ID
                {
                    None, /** No nature whatsoever */
                    Title, /** The title screen */
                    Menu, /** The menu screen */
                    Game, /** The playable area */
                    Pause, /** The pause screen */
                    Settings, /** The settings screen */
                };
            }
        }
    }
}

#endif //SOKOBAN_STATE_IDENTIFIERS_HPP
