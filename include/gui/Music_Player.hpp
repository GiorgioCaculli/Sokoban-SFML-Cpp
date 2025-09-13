#ifndef SOKOBAN_MUSIC_PLAYER_HPP
#define SOKOBAN_MUSIC_PLAYER_HPP

#include <ui/Resource_Holder.hpp>
#include <gui/Resource_Identifiers.hpp>

#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


namespace sokoban::ui::gui
{
    class Music_Player
    {
    public:
        Music_Player();

        void play( Music::ID song );

        void stop();

        void set_paused( bool paused );

        void set_volume( float volume );

        [[nodiscard]] float get_volume() const;

    private:
        sf::Music _music; /** The music handler */
        std::map< Music::ID, std::string > _filenames; /** The various files that can be played */
        float _volume; /** The music's volume */
    };
}


#endif //SOKOBAN_MUSIC_PLAYER_HPP
