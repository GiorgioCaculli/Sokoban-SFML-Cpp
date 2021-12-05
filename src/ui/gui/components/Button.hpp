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
                typedef std::shared_ptr< Button > Ptr;
                typedef std::function< void() > Callback;
                enum Type
                {
                    Normal,
                    Selected,
                    Pressed,
                    Button_Count
                };
                Button( State::Context context );
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
                Callback _callback;
                sf::Sprite _sprite;
                sf::Text _text;
                bool _is_toggled;
                Sound_Player &_sounds;
                void draw( sf::RenderTarget &target, sf::RenderStates states ) const;
                void change_texture( Type button_type );
            };
        }
    }
}

#endif //SOKOBAN_BUTTON_HPP
