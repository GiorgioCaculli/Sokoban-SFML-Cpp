#include "Music_Player.hpp"

#include <util/logger/Logger.hpp>

using namespace sokoban::ui::gui;
using namespace util;

namespace
{
    Logger logger( "Music Player", "sokoban.log", true );
}
/**
 * Default constructor for the music player
 */
Music_Player::Music_Player()
: _music()
, _filenames()
, _volume( 100.f )
{
    _filenames[ Music::Field_Desolate_Domain ] = "assets/music/Field_-_Desolate_Domain.ogg" ;
    _filenames[ Music::Field_Golden_Harvest ] = "assets/music/Field_-_Golden_Harvest.ogg" ;
    _filenames[ Music::Field_Greatest_Nation ] = "assets/music/Field_-_Greatest_Nation.ogg" ;
    _filenames[ Music::Field_Hades_Holiday ] = "assets/music/Field_-_Hades_Holiday.ogg" ;
    _filenames[ Music::Field_Homeland_Return ] = "assets/music/Field_-_Homeland_Return.ogg" ;
    _filenames[ Music::Field_Shattered_Land ] = "assets/music/Field_-_Shattered_Lands.ogg" ;
    _filenames[ Music::Theme_Courting_The_Princess ] = "assets/music/Theme_-_Courting_The_Princess.ogg" ;
    _filenames[ Music::Theme_Festival_Fun ] = "assets/music/Theme_-_Festival_Fun.ogg" ;
    _filenames[ Music::Theme_Funeral_March ] = "assets/music/Theme_-_Funeral_March.ogg" ;
    _filenames[ Music::Theme_Tournament_Time ] = "assets/music/Theme_-_Tournament_Time.ogg" ;
    _filenames[ Music::Town_Childhood_Home ] = "assets/music/Town_-_Childhood_Home.ogg" ;
    _filenames[ Music::Town_Fancy_Castle ] = "assets/music/Town_-_Fancy_Castle.ogg" ;
    _filenames[ Music::Town_Little_Village ] = "assets/music/Town_-_Little_Village.ogg" ;
    _filenames[ Music::Town_Nice_Day_Out ] = "assets/music/Town_-_Nice_Day_Out.ogg" ;
    _filenames[ Music::Town_Old_Palace ] = "assets/music/Town_-_Old_Palace.ogg" ;
    _filenames[ Music::Town_Peaceful_Place ] = "assets/music/Town_-_Peaceful_Place.ogg" ;
    _filenames[ Music::Town_Pleasant_peasants ] = "assets/music/Town_-_Pleasant_Peasants.ogg" ;
    _filenames[ Music::Town_Shop_Hopping ] = "assets/music/Town_-_Shop_Hopping.ogg" ;
    _filenames[ Music::Town_Spooky_Manor ] = "assets/music/Town_-_Spooky_Manor.ogg" ;
    _filenames[ Music::Town_Tavern_Tune ] = "assets/music/Town_-_Tavern_Tune.ogg" ;
}

/**
 * Function that plays a song based on its ID
 * @param song The song we wish to play
 */
void Music_Player::play( Music::ID song )
{
    std::string filename = _filenames[ song ];
    if( !_music.openFromFile( filename ) )
    {
        logger.log( Logger::Level::ERROR, "Music " + filename + " could not be loaded" );
        throw std::runtime_error( "Music " + filename + " could not be loaded" );
    }
    _music.setVolume( _volume );
    _music.setLoop( true );
    _music.play();
}

/**
 * Function meant to stop a song
 */
void Music_Player::stop()
{
    _music.stop();
}

/**
 * Function meant to pause a song
 * @param paused Whether the song is paused or not
 */
void Music_Player::set_paused( bool paused )
{
    if( paused )
    {
        _music.pause();
    }
    else
    {
        _music.play();
    }
}

/**
 * Volume setter for the song
 * @param volume The value of the volume
 */
void Music_Player::set_volume( float volume )
{
    _volume = volume;
    _music.setVolume( _volume );
}

/**
 * Getter for the volume
 * @return The current value of the volume
 */
float Music_Player::get_volume() const
{
    return _volume;
}
