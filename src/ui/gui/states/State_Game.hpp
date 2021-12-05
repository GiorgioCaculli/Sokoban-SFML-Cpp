#ifndef SOKOBAN_STATE_GAME_HPP
#define SOKOBAN_STATE_GAME_HPP

#include "State.hpp"
#include "../World.hpp"

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
                World *_world;
                sf::RenderWindow &_window;
                std::vector< std::string > _levels;
                std::string _level;
                sf::Text _text;
                void reset_board();
                void next_level();
                void prev_level();
            };
        }
    }
}

#endif //SOKOBAN_STATE_GAME_HPP
