#ifndef SOKOBAN_STATE_SETTINGS_HPP
#define SOKOBAN_STATE_SETTINGS_HPP

#include "State.hpp"
#include "../components/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <array>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Settings
                    : public State
            {
            public:
                State_Settings( State_Stack &stack, Context context );
                void draw() override;
                bool update( sf::Time dt ) override;
                bool handle_event( const sf::Event &event ) override;
            private:
                enum Options
                {
                    Music_Volume,
                    Effect_Volume,
                    Back,
                    Options_Count
                };
                enum Volume_Bars
                {
                    Music_Volume_Bar,
                    Effect_Volume_Bar,
                    Volume_Bars_Count
                };
                sf::Sprite _background_sprite;
                sf::Text _back_text;
                sf::Text _music_volume_text;
                sf::Text _effect_volume_text;
            };
        }
    }
}

#endif //SOKOBAN_STATE_SETTINGS_HPP
