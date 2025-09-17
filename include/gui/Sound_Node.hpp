#ifndef SOKOBAN_SOUND_NODE_HPP
#define SOKOBAN_SOUND_NODE_HPP

#include "ui/Category.hpp"
#include <gui/Scene_Node.hpp>
#include <gui/Resource_Identifiers.hpp>


namespace sokoban::ui::gui
{
    class Sound_Player;

    class Sound_Node
            : private Scene_Node
    {
    public:
        explicit Sound_Node( Sound_Player& player );

        void play_sound( Sound_Effect::ID sound, sf::Vector2f position ) const;

        Category::Type get_category() const override;

    private:
        Sound_Player& _sounds; /** The sound player for the current sound node */
    };
}


#endif //SOKOBAN_SOUND_NODE_HPP
