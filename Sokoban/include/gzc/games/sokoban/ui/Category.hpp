#ifndef SOKOBAN_CATEGORY_HPP
#define SOKOBAN_CATEGORY_HPP

namespace sokoban
{
    namespace ui
    {
        namespace Category
        {
            /**
             * Various types of actors and effects could be initialized
             */
            enum Type
            {
                None = 0, /** Absolute nothing */
                Scene = 1 << 0, /** The actual Scene */
                Player = 1 << 1, /** The player itself */
                Box = 1 << 2, /** The various boxes */
                Platform = 1 << 3, /** The various platforms */
                Wall = 1 << 4, /** The various walls */
                Player_Movement = 1 << 5, /** The effect concerning the player movement */
                Box_Movement = 1 << 6, /** The effect concerning the box's movement */
                Sound_Effect = 1 << 7, /** Any various sound effect */

                Actor = Player | Box | Platform | Wall,
            };
        }
    }
}

#endif //SOKOBAN_CATEGORY_HPP
