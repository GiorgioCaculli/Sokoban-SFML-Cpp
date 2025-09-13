#ifndef SOKOBAN_STATE_MENU_HPP
#define SOKOBAN_STATE_MENU_HPP

#include <gui/states/State.hpp>
#include <gui/components/Container.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <gui/components/Button.hpp>

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
        Button::Ptr _play_button;
        Button::Ptr _settings_button;
        Button::Ptr _exit_button;
        bool handle_keyboard_events(const sf::Event& event) override;
        bool handle_mouse_events(const sf::Event& event) override;
    };
}


#endif //SOKOBAN_STATE_MENU_HPP
