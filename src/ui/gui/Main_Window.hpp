#ifndef SOKOBAN_MAIN_WINDOW_HPP
#define SOKOBAN_MAIN_WINDOW_HPP

#include "../../util/Logger.hpp"
#include "../../model/Board.hpp"
#include "Game_Scene_Node.hpp"

#include <SFML/System/Time.hpp>
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
                static const sf::Time time_per_frame;
                sf::RenderWindow window;
                GameSceneNode *game;
                sf::Font font;
                sf::Text statistics_text;
                sf::Time statistics_update_time;
                std::size_t statistics_num_frames;
                void update_statistics( sf::Time elapsed_time );
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
