#ifndef SOKOBAN_MUSIC_PLAYER_HPP
#define SOKOBAN_MUSIC_PLAYER_HPP

#include <gzc/games/sokoban/ui/Resource_Holder.hpp>
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
                float get_volume() const;
            private:
                sf::Music _music; /** The music handler */
                std::map< Music::ID, std::string > _filenames; /** The various files that can be played */
                float _volume; /** The music's volume */
            };
        }
    }
}

#endif //SOKOBAN_MUSIC_PLAYER_HPP
