#ifndef SOKOBAN_STATE_GAME_HPP
#define SOKOBAN_STATE_GAME_HPP

#include "State.hpp"
#include <gzc/games/sokoban/ui/gui/sfml/World.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Game
                    : public State
            {
            public:
                State_Game( State_Stack &stack, Context context );
                ~State_Game() override;
                bool update( sf::Time dt ) override;
                void draw() override;
                bool handle_event( const sf::Event &event ) override;
            private:
                World *_world; /** The map that has to be displayed */
                sf::RenderWindow &_window; /** The window where everything has to be drawn into */
                std::vector< std::string > _levels; /** The various levels throughout the game */
                std::string _level; /** The level that is currently being played */
                sf::Text _text; /** The textual information present on the screen */
                void reset_board();
                void next_level();
                void prev_level();
            };
        }
    }
}

#endif //SOKOBAN_STATE_GAME_HPP
