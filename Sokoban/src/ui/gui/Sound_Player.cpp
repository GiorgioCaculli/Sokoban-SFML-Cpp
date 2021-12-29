#include "Sound_Player.hpp"

#include <util/logger/Logger.hpp>

#include <SFML/Audio/Listener.hpp>

#include <cmath>

using namespace sokoban::ui::gui;
using namespace util;

namespace
{
    const float Listener_Z = 0.f;
    const float Attenuation = 8.f;
    const float Min_Distance_2D = 0.f;
    const float Min_Distance_3D = std::sqrt( Min_Distance_2D * Min_Distance_2D + Listener_Z * Listener_Z );
}

/**
 * Default constructor for the Sound Player
 */
Sound_Player::Sound_Player()
: _sound_buffers()
, _sounds()
, _volume( 100.f )
{
    _sound_buffers.load( Sound_Effect::Button_Beep_01, "assets/sounds/button_beep_01.ogg" );
    _sound_buffers.load( Sound_Effect::Button_Beep_02, "assets/sounds/button_beep_02.ogg" );
    _sound_buffers.load( Sound_Effect::Button_Click_01, "assets/sounds/button_click_01.ogg" );
    _sound_buffers.load( Sound_Effect::Button_Click_02, "assets/sounds/button_click_02.ogg" );
    _sound_buffers.load( Sound_Effect::Button_Click_03, "assets/sounds/button_click_03.ogg" );
    _sound_buffers.load( Sound_Effect::Button_Pop_01, "assets/sounds/button_pop_01.ogg" );
    _sound_buffers.load( Sound_Effect::Button_Pop_02, "assets/sounds/button_pop_02.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Outdoor_Boots, "assets/sounds/footsteps_outdoor_boots.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Outdoor_Boots_On_Wood, "assets/sounds/footsteps_outdoor_boots_on_wood.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Shoes_Fast_01, "assets/sounds/footsteps_shoes_fast_01.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Shoes_On_Wood_01, "assets/sounds/footsteps_shoes_on_wood_01.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Shoes_On_Wood_02, "assets/sounds/footsteps_shoes_on_wood_02.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Snow_01, "assets/sounds/footsteps_snow_01.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Snow_02, "assets/sounds/footsteps_snow_02.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Soft_Fast, "assets/sounds/footsteps_soft_fast.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Stair_Ascent_Creaky, "assets/sounds/footsteps_stair_ascent_creaky.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Water_01, "assets/sounds/footsteps_water_01.ogg" );
    _sound_buffers.load( Sound_Effect::Player_Footsteps_Water_02, "assets/sounds/footsteps_water_02.ogg" );
    for( sf::Sound sound : _sounds )
    {
        sound.setVolume( _volume );
    }
    sf::Listener::setDirection( 0.f, 0.f, -1.f );
}

/**
 * Function meant to play a sound effect
 * @param effect The sound effect to play
 */
void Sound_Player::play( Sound_Effect::ID effect )
{
    play( effect, get_listener_position() );
}

/**
 * Function meant to play a sound effect depending on its position
 * @param effect The sound effect to play
 * @param position The position that defines when a sound effect is played
 */
void Sound_Player::play( Sound_Effect::ID effect, sf::Vector2f position )
{
    _sounds.emplace_back( sf::Sound() );
    sf::Sound &sound = _sounds.back();

    sound.setBuffer( _sound_buffers.get( effect ) );
    sound.setPosition( position.x, position.y, 0.f );
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
    _sounds.remove_if( [] ( const sf::Sound &s ) {
        return s.getStatus() == sf::Sound::Stopped;
    } );
}

/**
 * Set the sound effect position
 * @param position The position meant to be listened
 */
void Sound_Player::set_listener_position( sf::Vector2f position )
{
    sf::Listener::setPosition( position.x, position.y, Listener_Z );
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
void Sound_Player::set_volume( float volume )
{
    _volume = volume;
    for( sf::Sound sound : _sounds )
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
