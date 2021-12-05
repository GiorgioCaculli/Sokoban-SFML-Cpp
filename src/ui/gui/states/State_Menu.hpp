#ifndef SOKOBAN_STATE_MENU_HPP
#define SOKOBAN_STATE_MENU_HPP

#include "State.hpp"
#include "../components/Container.hpp"

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
                sf::Sprite _background_sprite;
                Container _container;
            };
        }
    }
}

#endif //SOKOBAN_STATE_MENU_HPP
