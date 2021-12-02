#ifndef SOKOBAN_APPLICATION_HPP
#define SOKOBAN_APPLICATION_HPP

#include "../../util/Logger.hpp"
#include "../Resource_Holder.hpp"
#include "Resource_Identifiers.hpp"
#include "states/State_Stack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            using namespace sokoban::util;

            class Application
                    : private sf::NonCopyable
            {
            public:
                Application();
                ~Application();
                unsigned short run();
            private:
                static const sf::Time time_per_frame;
                sf::RenderWindow _window;
                Texture_Holder _textures;
                Font_Holder _fonts;
                State_Stack _state_stack;
                sf::Text _statistics_text;
                sf::Time _statistics_update_time;
                std::size_t _statistics_num_frames;
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
