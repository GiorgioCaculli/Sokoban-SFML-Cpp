#ifndef SOKOBAN_STATE_TITLE_HPP
#define SOKOBAN_STATE_TITLE_HPP

#include <ui/gui/states/State.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>


namespace sokoban::ui::gui
{
    class State_Title
            : public State
    {
    public:
        State_Title( State_Stack& stack, Context context );

        void draw() override;

        bool update( sf::Time dt ) override;

        bool handle_event( const sf::Event& event ) override;

    private:
        sf::Sprite _background_sprite; /** The background sprite */
        sf::Text _text; /** The flashing text */
        sf::Text _title_text; /** The text in japanese stating Sokoban */
        sf::Text _title_sub_text; /** The sub text translating Sokoban from Japanese */
        bool _show_text; /** Bool that states whether the text has to be hidden or not */
        sf::Time _text_effect_time; /** Timer for the text to blink */
    };
}


#endif //SOKOBAN_STATE_TITLE_HPP
