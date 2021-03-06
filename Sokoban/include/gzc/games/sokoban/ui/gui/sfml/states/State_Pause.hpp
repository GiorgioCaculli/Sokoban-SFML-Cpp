#ifndef SOKOBAN_STATE_PAUSE_HPP
#define SOKOBAN_STATE_PAUSE_HPP

#include "State.hpp"
#include <gzc/games/sokoban/ui/gui/sfml/components/Container.hpp>

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
                sf::Sprite _background_sprite; /** The background sprite */
                sf::Text _paused_text; /** The text stating that the game is paused */
                Container _container; /** Container containing the various components */
            };
        }
    }
}

#endif //SOKOBAN_STATE_PAUSE_HPP
