#ifndef SOKOBAN_BUTTON_HPP
#define SOKOBAN_BUTTON_HPP

#include "Component.hpp"
#include "../Resource_Identifiers.hpp"
#include "../states/State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>
#include <string>
#include <vector>
#include <functional>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Sound_Player;
            class Button
                    : public Component
            {
            public:
                typedef std::shared_ptr< Button > Ptr; /** The shared pointer that will define the Component's nature */
                typedef std::function< void() > Callback; /** The action the component will execute */
                enum Type
                {
                    Normal, /** Non-selected state of a button */
                    Selected, /** Selected state of a button */
                    Pressed, /** Pressed state of a button */
                    Button_Count /** Counter for various button states */
                };
                explicit Button( State::Context context );
                void set_callback( Callback callback );
                void set_text( const std::string &text );
                void set_toggle( bool flag );
                bool is_selectable() const override;
                void select() override;
                void deselect() override;
                void activate() override;
                void deactivate() override;
                void handle_event( const sf::Event &event ) override;
            private:
                Callback _callback; /** The type of execution the button will cause */
                sf::Sprite _sprite; /** The asset meant to represent the sprite */
                sf::Text _text; /** The text written on the button */
                bool _is_toggled; /** Whether the button is toggled or not */
                Sound_Player &_sounds; /** The sound it will make when selected or executed */
                void draw( sf::RenderTarget &target, sf::RenderStates states ) const override;
                void change_texture( Type button_type );
            };
        }
    }
}

#endif //SOKOBAN_BUTTON_HPP
