#ifndef SOKOBAN_STATE_PAUSE_HPP
#define SOKOBAN_STATE_PAUSE_HPP

#include <gui/states/State.hpp>
#include <gui/components/Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <gui/components/Button.hpp>


namespace sokoban::ui::gui
{
    class State_Pause final
            : public State
    {
    public:
        State_Pause( State_Stack& stack, const Context& context );

        void draw() override;

        bool update( sf::Time dt ) override;

        bool handle_event( const sf::Event& event ) override;

    private:
        sf::Sprite _background_sprite; /** The background sprite */
        sf::Text _paused_text; /** The text stating that the game is paused */
        Container _container; /** Container containing the various components */
        Button::Ptr _resume_button;
        Button::Ptr _settings_button;
        Button::Ptr _back_to_main_menu_button;
        bool handle_keyboard_events(const sf::Event& event) override;
        bool handle_mouse_events(const sf::Event& event) override;
        bool _resume_button_callback() const;
        bool _settings_button_callback() const;
        bool _back_to_main_menu_button_callback() const;
    };
}


#endif //SOKOBAN_STATE_PAUSE_HPP
