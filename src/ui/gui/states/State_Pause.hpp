#ifndef SOKOBAN_STATE_PAUSE_HPP
#define SOKOBAN_STATE_PAUSE_HPP

#include "State.hpp"
#include "../components/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Pause
                    : public State
            {
            public:
                State_Pause( State_Stack &stack, Context context );
                void draw() override;
                bool update( sf::Time dt ) override;
                bool handle_event( const sf::Event &event ) override;
            private:
                sf::Sprite _background_sprite;
                sf::Text _paused_text;
                Container _container;
            };
        }
    }
}

#endif //SOKOBAN_STATE_PAUSE_HPP
