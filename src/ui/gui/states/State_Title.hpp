#ifndef SOKOBAN_STATE_TITLE_HPP
#define SOKOBAN_STATE_TITLE_HPP

#include "State.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Title
                    : public State
            {
            public:
                State_Title( State_Stack &stack, Context context );
                void draw() override;
                bool update( sf::Time dt ) override;
                bool handle_event( const sf::Event &event ) override;
            private:
                sf::Sprite _background_sprite;
                sf::Text _text;
                sf::Text _title_text;
                bool _show_text;
                sf::Time _text_effect_time;
            };
        }
    }
}

#endif //SOKOBAN_STATE_TITLE_HPP
