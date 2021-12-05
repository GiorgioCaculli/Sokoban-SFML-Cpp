#ifndef SOKOBAN_CATEGORY_HPP
#define SOKOBAN_CATEGORY_HPP

namespace sokoban
{
    namespace ui
    {
        namespace Category
        {
            enum Type
            {
                None = 0,
                Scene = 1 << 0,
                Player = 1 << 1,
                Box = 1 << 2,
                Platform = 1 << 3,
                Wall = 1 << 4,
                Player_Movement = 1 << 5,
                Box_Movement = 1 << 6,
                Sound_Effect = 1 << 7,

                Actor = Player | Box | Platform | Wall,
            };
        }
    }
}

#endif //SOKOBAN_CATEGORY_HPP
