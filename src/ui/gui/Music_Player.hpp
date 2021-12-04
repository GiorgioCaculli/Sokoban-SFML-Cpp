#ifndef SOKOBAN_MUSIC_PLAYER_HPP
#define SOKOBAN_MUSIC_PLAYER_HPP

#include "../Resource_Holder.hpp"
#include "Resource_Identifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Music_Player
        : private sf::NonCopyable
            {
            public:
                Music_Player();
                void play( Music::ID song );
                void stop();
                void set_paused( bool paused );
                void set_volume( float volume );
            private:
                sf::Music _music;
                std::map< Music::ID, std::string > _filenames;
                float _volume;
            };
        }
    }
}

#endif //SOKOBAN_MUSIC_PLAYER_HPP
