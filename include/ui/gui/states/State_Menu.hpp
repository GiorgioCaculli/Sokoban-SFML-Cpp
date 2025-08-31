#ifndef SOKOBAN_STATE_MENU_HPP
#define SOKOBAN_STATE_MENU_HPP

#include <ui/gui/states/State.hpp>
#include <ui/gui/components/Container.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sokoban::ui::gui
{
    class State_Menu final
            : public State
    {
    public:
        State_Menu( State_Stack& stack, Context context );

        void draw() override;

        bool update( sf::Time dt ) override;

        bool handle_event( const sf::Event& event ) override;

    private:
        sf::Sprite _background_sprite; /** The background sprite */
        Container _container; /** Container storing the various components */
    };
}


#endif //SOKOBAN_STATE_MENU_HPP
