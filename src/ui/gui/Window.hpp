#ifndef SOKOBAN_WINDOW_HPP
#define SOKOBAN_WINDOW_HPP

#include "../../util/Logger.hpp"
#include "../../model/Board.hpp"
#include "State_Game.hpp"

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

            class MainWindow
                    : private sf::NonCopyable
            {
            private:
                static const sf::Time _time_per_frame;
                sf::RenderWindow _window;
                State_Game *_game;
                sf::Font _font;
                sf::Text _statistics_text;
                sf::Time _statistics_update_time;
                std::size_t _statistics_num_frames;
                void update_statistics( sf::Time elapsed_time );
                void update( const sf::Time &delta_time );
                void render();
            public:
                MainWindow();
                ~MainWindow();
                unsigned short run();
            };
        }
    }
}

#endif //SOKOBAN_WINDOW_HPP
