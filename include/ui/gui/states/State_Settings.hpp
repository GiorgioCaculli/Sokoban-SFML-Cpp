#ifndef SOKOBAN_STATE_SETTINGS_HPP
#define SOKOBAN_STATE_SETTINGS_HPP

#include <ui/gui/states/State.hpp>
#include <ui/gui/components/Container.hpp>
#include <ui/gui/components/Button.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


namespace sokoban::ui::gui
{
    class State_Settings final
            : public State
    {
    public:
        State_Settings( State_Stack& stack, Context context );

        void draw() override;

        bool update( sf::Time dt ) override;

        bool handle_event( const sf::Event& event ) override;

    private:
        sf::Sprite _background_sprite; /** The background sprite */
        sf::Text _settings_text; /** The text stating Settings */
        Container _container; /** The container containing the various components */
        Button::Ptr _music_volume_button; /** The music volume button */
        Button::Ptr _sound_effect_volume_button; /** The sound effect volume button */
        Button::Ptr _network_button; /** Button to activate network features */
        Button::Ptr _back_button;
        void change_sound_effect_volume( float val ) const;
        void change_music_volume( float val ) const;
        bool handle_keyboard_events(const sf::Event& event) override;
        bool handle_mouse_events(const sf::Event& event) override;
    };
}


#endif //SOKOBAN_STATE_SETTINGS_HPP
