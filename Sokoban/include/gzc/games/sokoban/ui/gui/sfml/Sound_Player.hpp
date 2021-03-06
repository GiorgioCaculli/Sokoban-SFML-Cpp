#ifndef SOKOBAN_SOUND_PLAYER_HPP
#define SOKOBAN_SOUND_PLAYER_HPP

#include <gzc/games/sokoban/ui/Resource_Holder.hpp>
#include "Resource_Identifiers.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Sound_Player
        : private sf::NonCopyable
            {
            public:
                Sound_Player();
                void play( Sound_Effect::ID effect );
                void play( Sound_Effect::ID effect, sf::Vector2f position );
                void remove_stopped_sounds();
                void set_listener_position( sf::Vector2f position );
                sf::Vector2f get_listener_position() const;
                void set_volume( float volume );
                float get_volume() const;
            private:
                Sound_Buffer_Holder _sound_buffers; /** Sound Effect Holder */
                std::list< sf::Sound > _sounds; /** List containing the various sound effects */
                float _volume; /** The sound effects' volume */
            };
        }
    }
}

#endif //SOKOBAN_SOUND_PLAYER_HPP
