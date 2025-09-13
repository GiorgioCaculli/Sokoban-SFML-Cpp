#ifndef SOKOBAN_STATE_GAME_HPP
#define SOKOBAN_STATE_GAME_HPP

#include <gui/states/State.hpp>
#include <gui/World.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <gzc/util/logger/Logger.hpp>


namespace sokoban::ui::gui
{
    class State_Game final
            : public State
    {
    public:
        State_Game( State_Stack& stack, Context context );

        ~State_Game() override;

        bool update( sf::Time dt ) override;

        void draw() override;

        bool handle_event( const sf::Event& event ) override;

    private:
        unsigned long current_level = 0;
        int reset_counter = 0;
        const gzc::util::logger::Logger logger = gzc::util::logger::Logger("State Game", "sokoban.log", true );
        World* _world; /** The map that has to be displayed */
        sf::RenderWindow& _window; /** The window where everything has to be drawn into */
        std::vector< std::string > _levels; /** The various levels throughout the game */
        std::string _level; /** The level that is currently being played */
        sf::Text _text; /** The textual information present on the screen */
        void reset_board();

        void next_level();

        void prev_level();
        bool handle_keyboard_events(const sf::Event& event) override;
        bool handle_mouse_events(const sf::Event& event) override;
    };
}


#endif //SOKOBAN_STATE_GAME_HPP
