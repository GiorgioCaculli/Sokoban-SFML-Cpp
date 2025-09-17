#include <gui/Music_Player.hpp>

#include <gzc/util/logger/Logger.hpp>

using namespace sokoban::ui::gui;
using namespace gzc::util::logger;

namespace
{
    Logger logger( "Music Player", "sokoban.log", true );
}

/**
 * Default constructor for the music player
 */
Music_Player::Music_Player()
    : _volume( 100.f )
{
    using enum Music::ID;
    _filenames[ Field_Desolate_Domain ] = "res/music/Field_-_Desolate_Domain.ogg";
    _filenames[ Field_Golden_Harvest ] = "res/music/Field_-_Golden_Harvest.ogg";
    _filenames[ Field_Greatest_Nation ] = "res/music/Field_-_Greatest_Nation.ogg";
    _filenames[ Field_Hades_Holiday ] = "res/music/Field_-_Hades_Holiday.ogg";
    _filenames[ Field_Homeland_Return ] = "res/music/Field_-_Homeland_Return.ogg";
    _filenames[ Field_Shattered_Land ] = "res/music/Field_-_Shattered_Lands.ogg";
    _filenames[ Theme_Courting_The_Princess ] = "res/music/Theme_-_Courting_The_Princess.ogg";
    _filenames[ Theme_Festival_Fun ] = "res/music/Theme_-_Festival_Fun.ogg";
    _filenames[ Theme_Funeral_March ] = "res/music/Theme_-_Funeral_March.ogg";
    _filenames[ Theme_Tournament_Time ] = "res/music/Theme_-_Tournament_Time.ogg";
    _filenames[ Town_Childhood_Home ] = "res/music/Town_-_Childhood_Home.ogg";
    _filenames[ Town_Fancy_Castle ] = "res/music/Town_-_Fancy_Castle.ogg";
    _filenames[ Town_Little_Village ] = "res/music/Town_-_Little_Village.ogg";
    _filenames[ Town_Nice_Day_Out ] = "res/music/Town_-_Nice_Day_Out.ogg";
    _filenames[ Town_Old_Palace ] = "res/music/Town_-_Old_Palace.ogg";
    _filenames[ Town_Peaceful_Place ] = "res/music/Town_-_Peaceful_Place.ogg";
    _filenames[ Town_Pleasant_peasants ] = "res/music/Town_-_Pleasant_Peasants.ogg";
    _filenames[ Town_Shop_Hopping ] = "res/music/Town_-_Shop_Hopping.ogg";
    _filenames[ Town_Spooky_Manor ] = "res/music/Town_-_Spooky_Manor.ogg";
    _filenames[ Town_Tavern_Tune ] = "res/music/Town_-_Tavern_Tune.ogg";
}

/**
 * Function that plays a song based on its ID
 * @param song The song we wish to play
 */
void Music_Player::play( const Music::ID song )
{
    if ( const std::string filename = _filenames[ song ]; !_music.openFromFile( filename ) )
    {
        logger.log( Logger::Level::ERROR, "Music " + filename + " could not be loaded" );
        throw std::runtime_error( "Music " + filename + " could not be loaded" );
    }
    _music.setVolume( _volume );
    _music.setLooping( true );
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
void Music_Player::set_paused( const bool paused )
{
    if ( paused )
    {
        _music.pause();
    } else
    {
        _music.play();
    }
}

/**
 * Volume setter for the song
 * @param volume The value of the volume
 */
void Music_Player::set_volume( const float volume )
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
