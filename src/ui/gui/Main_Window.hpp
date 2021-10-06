#ifndef SOKOBAN_MAIN_WINDOW_HPP
#define SOKOBAN_MAIN_WINDOW_HPP

#include "../../util/logger.hpp"
#include "../../model/Board.hpp"
#include "Game_Scene_Node.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            using namespace sokoban::util;
            using namespace sokoban::model;

            class MainFrame
                    : private sf::NonCopyable
            {
            private:
                Logger *logger {};
                static const sf::Time time_per_frame;
                sf::RenderWindow window;
                GameSceneNode *game;
                sf::Font font;
                sf::Text statistics_text;
                sf::Time statistics_update_time;
                std::size_t statistics_num_frames;
                bool player_is_moving_up;
                bool player_is_moving_down;
                bool player_is_moving_left;
                bool player_is_moving_right;
                void handle_player_input( sf::Keyboard::Key key, bool is_pressed );
                void update_statistics( sf::Time elapsed_time );
                void process_events();
                void update( sf::Time delta_time );
                void render();
            public:
                MainFrame();
                ~MainFrame();
                unsigned short run();
            };
        }
    }
}

#endif //SOKOBAN_MAIN_WINDOW_HPP
