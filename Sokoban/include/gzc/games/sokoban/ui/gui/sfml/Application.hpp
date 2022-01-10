#ifndef SOKOBAN_APPLICATION_HPP
#define SOKOBAN_APPLICATION_HPP

#include <gzc/logger/Logger.hpp>
#include <gzc/games/sokoban/ui/Resource_Holder.hpp>
#include "Resource_Identifiers.hpp"
#include <gzc/games/sokoban/ui/gui/sfml/entities/Entity_Player.hpp>
#include <gzc/games/sokoban/ui/gui/sfml/states/State_Stack.hpp>
#include "Music_Player.hpp"
#include "Sound_Player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            using namespace util;

            class Application
                    : private sf::NonCopyable
            {
            public:
                Application();
                ~Application();
                unsigned short run();
            private:
                static const sf::Time _time_per_frame; /** The amount of frames per second we wish to display */
                sf::RenderWindow _window; /** The window where the drawables are shown */
                Texture_Holder _textures; /** The default texture holder */
                Font_Holder _fonts; /** The default font holder */
                Music_Player _music; /** The default music player */
                Sound_Player _sounds; /** The default sound player */
                State_Stack _state_stack; /** The stack containing the various states */
                sf::Text _statistics_text; /** Text with the FPS amount */
                sf::Time _statistics_update_time; /** Timer to update the various statistics */
                std::size_t _statistics_num_frames; /** Number of frames per second globally */
                void process_input();
                void update( const sf::Time &delta_time );
                void render();
                void update_statistics( sf::Time dt );
                void register_states();
            };
        }
    }
}

#endif //SOKOBAN_APPLICATION_HPP
