#ifndef SOKOBAN_STATE_SETTINGS_HPP
#define SOKOBAN_STATE_SETTINGS_HPP

#include "State.hpp"
#include "../entities/Entity_Player.hpp"
#include "../Container.hpp"
#include "../Button.hpp"
#include "../Label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            namespace state
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
                    Container _container;
                    std::array< Button::Ptr, 0 > _binding_buttons;
                    std::array< Label::Ptr, 0 > _binding_labels;
                    void update_labels();
                };
            }
        }
    }
}

#endif //SOKOBAN_STATE_SETTINGS_HPP
