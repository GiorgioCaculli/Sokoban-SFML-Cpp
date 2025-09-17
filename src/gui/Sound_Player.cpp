#include <gui/Sound_Player.hpp>

#include <gzc/util/logger/Logger.hpp>

#include <SFML/Audio/Listener.hpp>

#include <cmath>

using namespace sokoban::ui::gui;
using namespace gzc::util::logger;

namespace
{
    constexpr float Listener_Z = 0.f;
    constexpr float Attenuation = 8.f;
    constexpr float Min_Distance_2D = 0.f;
    const float Min_Distance_3D = std::sqrt( Min_Distance_2D * Min_Distance_2D + Listener_Z * Listener_Z );
}

/**
 * Default constructor for the Sound Player
 */
Sound_Player::Sound_Player( const float volume )
: _volume( volume )
{
    using enum Sound_Effect::ID;
    _sound_buffers.load( Button_Beep_01, "res/sounds/button_beep_01.ogg" );
    _sound_buffers.load( Button_Beep_02, "res/sounds/button_beep_02.ogg" );
    _sound_buffers.load( Button_Click_01, "res/sounds/button_click_01.ogg" );
    _sound_buffers.load( Button_Click_02, "res/sounds/button_click_02.ogg" );
    _sound_buffers.load( Button_Click_03, "res/sounds/button_click_03.ogg" );
    _sound_buffers.load( Button_Pop_01, "res/sounds/button_pop_01.ogg" );
    _sound_buffers.load( Button_Pop_02, "res/sounds/button_pop_02.ogg" );
    _sound_buffers.load( Player_Footsteps_Outdoor_Boots, "res/sounds/footsteps_outdoor_boots.ogg" );
    _sound_buffers.load( Player_Footsteps_Outdoor_Boots_On_Wood,
                         "res/sounds/footsteps_outdoor_boots_on_wood.ogg" );
    _sound_buffers.load( Player_Footsteps_Shoes_Fast_01, "res/sounds/footsteps_shoes_fast_01.ogg" );
    _sound_buffers.load( Player_Footsteps_Shoes_On_Wood_01, "res/sounds/footsteps_shoes_on_wood_01.ogg" );
    _sound_buffers.load( Player_Footsteps_Shoes_On_Wood_02, "res/sounds/footsteps_shoes_on_wood_02.ogg" );
    _sound_buffers.load( Player_Footsteps_Snow_01, "res/sounds/footsteps_snow_01.ogg" );
    _sound_buffers.load( Player_Footsteps_Snow_02, "res/sounds/footsteps_snow_02.ogg" );
    _sound_buffers.load( Player_Footsteps_Soft_Fast, "res/sounds/footsteps_soft_fast.ogg" );
    _sound_buffers.load( Player_Footsteps_Stair_Ascent_Creaky,
                         "res/sounds/footsteps_stair_ascent_creaky.ogg" );
    _sound_buffers.load( Player_Footsteps_Water_01, "res/sounds/footsteps_water_01.ogg" );
    _sound_buffers.load( Player_Footsteps_Water_02, "res/sounds/footsteps_water_02.ogg" );
    for ( sf::Sound sound: _sounds )
    {
        sound.setVolume( _volume );
    }
    sf::Listener::setDirection( sf::Vector3f( 0.f, 0.f, -1.f ) );
}

Sound_Player::Sound_Player()
    : Sound_Player( 100.f )
{
}

Sound_Player::Sound_Player( const Sound_Player& s )
: Sound_Player( s.get_volume() )
{
}

Sound_Player& Sound_Player::operator=( const Sound_Player& s )
{
    if( this != &s )
    {
        _volume = s.get_volume();
    }
    return *this;
}

/**
 * Function meant to play a sound effect
 * @param effect The sound effect to play
 */
void Sound_Player::play( const Sound_Effect::ID effect )
{
    play( effect, get_listener_position() );
}

/**
 * Function meant to play a sound effect depending on its position
 * @param effect The sound effect to play
 * @param position The position that defines when a sound effect is played
 */
void Sound_Player::play( const Sound_Effect::ID effect, const sf::Vector2f position )
{
    _sounds.emplace_back( _sound_buffers.get( effect ) );
    sf::Sound& sound = _sounds.back();

    sound.setPosition( sf::Vector3f( position.x, position.y, 0.f ) );
    sound.setAttenuation( Attenuation );
    sound.setMinDistance( Min_Distance_3D );
    sound.setVolume( _volume );

    sound.play();
}

/**
 * Function that removes all stopped sounds
 */
void Sound_Player::remove_stopped_sounds()
{
    _sounds.remove_if( []( const sf::Sound& s )
    {
        return s.getStatus() == sf::Sound::Status::Stopped;
    } );
}

/**
 * Set the sound effect position
 * @param position The position meant to be listened
 */
void Sound_Player::set_listener_position( const sf::Vector2f position ) const
{
    sf::Listener::setPosition( sf::Vector3f( position.x, position.y, Listener_Z ) );
}

/**
 * Getter for the sound effect position
 * @return The position of the sound effect
 */
sf::Vector2f Sound_Player::get_listener_position() const
{
    sf::Vector3f position = sf::Listener::getPosition();
    return { position.x, position.y };
}

/**
 * Volume setter for the various sound effects
 * @param volume The value of volume to set
 */
void Sound_Player::set_volume( const float volume )
{
    _volume = volume;
    for ( sf::Sound sound: _sounds )
    {
        sound.setVolume( _volume );
    }
}

/**
 * Getter for the value of volume
 * @return The value of the sound effects volume
 */
float Sound_Player::get_volume() const
{
    return _volume;
}
