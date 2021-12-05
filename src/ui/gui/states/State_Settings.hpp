#ifndef SOKOBAN_STATE_SETTINGS_HPP
#define SOKOBAN_STATE_SETTINGS_HPP

#include "State.hpp"
#include "../components/Container.hpp"
#include "../components/Button.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

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
                sf::Sprite _background_sprite;
                sf::Text _settings_text;
                Container _container;
                Button::Ptr _music_volume_button;
                Button::Ptr _sound_effect_volume_button;
            };
        }
    }
}

#endif //SOKOBAN_STATE_SETTINGS_HPP
