#ifndef SOKOBAN_MAIN_FRAME_HPP
#define SOKOBAN_MAIN_FRAME_HPP

#include "../../util/logger.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            using namespace sokoban::util;

            class MainFrame
            {
            private:
                unsigned short _width{};
                unsigned short _height{};
                Logger *logger{};
                sf::RenderWindow *window;
                sf::Sprite *player;
                sf::Texture *player_texture;
                bool player_is_moving_up;
                bool player_is_moving_down;
                bool player_is_moving_left;
                bool player_is_moving_right;
                static const sf::Time time_per_frame;
                static const float player_speed;

            private:
                void handle_player_input( sf::Keyboard::Key key, bool is_pressed );

                void process_events();

                void update( sf::Time delta_time );

                void render();

            public:
                MainFrame( unsigned short width, unsigned short height );

                MainFrame();

                ~MainFrame();

                void set_width( unsigned short width );

                unsigned short get_width() const;

                void set_height( unsigned short height );

                unsigned short get_height() const;

                unsigned short run();
            };
        }
    }
}

#endif //SOKOBAN_MAIN_FRAME_HPP
