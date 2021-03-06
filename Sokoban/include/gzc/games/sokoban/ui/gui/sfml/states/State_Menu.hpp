#ifndef SOKOBAN_STATE_MENU_HPP
#define SOKOBAN_STATE_MENU_HPP

#include "State.hpp"
#include <gzc/games/sokoban/ui/gui/sfml/components/Container.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Menu
                    : public State
            {
            public:
                State_Menu( State_Stack &stack, Context context );
                void draw() override;
                bool update( sf::Time dt ) override;
                bool handle_event( const sf::Event &event ) override;
            private:
                sf::Sprite _background_sprite; /** The background sprite */
                Container _container; /** Container storing the various components */
            };
        }
    }
}

#endif //SOKOBAN_STATE_MENU_HPP
