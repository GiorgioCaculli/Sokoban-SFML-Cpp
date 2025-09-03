#include <ui/gui/states/State_Settings.hpp>

#include <ui/gui/components/Button.hpp>
#include <ui/gui/Utility.hpp>
#include <ui/Resource_Holder.hpp>
#include <ui/gui/Music_Player.hpp>
#include <ui/gui/Sound_Player.hpp>
#include <ui/gui/components/Label.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;

namespace
{
    float tmp_music_vol;
    float tmp_sound_effect_vol;
}

/**
 * Default constructor for the Settings state
 * @param stack The stack containing the various states
 * @param context The context containing the globally accessible resources
 */
State_Settings::State_Settings( State_Stack& stack, Context context )
    : State( stack, context )
    , _background_sprite( context._textures->get( Textures::Title_Screen ) )
    , _settings_text( context._fonts->get( Fonts::Rampart_One ) )
{
    const sf::Vector2f view_size = context._window->getView().getSize();

    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( view_size / 2.f );

    /* Initialize buttons */
    _music_volume_button = std::make_shared< Button >( context );
    _music_volume_button->set_text( std::to_string( static_cast< int >( get_context()._music->get_volume() ) ) );
    _music_volume_button->set_toggle( true );

    _sound_effect_volume_button = std::make_shared< Button >( context );
    _sound_effect_volume_button->set_text( std::to_string( static_cast< int >( get_context()._sounds->get_volume() ) ) );
    _sound_effect_volume_button->set_toggle( true );

    _network_button = std::make_shared< Button >( context );
    _network_button->set_text( "Disabled" );
    _network_button->set_toggle( false );

    const auto back_button = std::make_shared< Button >( context );
    back_button->set_text( "Back" );
    back_button->set_callback( [ this ]
    {
        request_stack_pop();
    } );

    /* Position buttons and related labels */
    _sound_effect_volume_button->setPosition( sf::Vector2f( view_size.x / 2.f, ( view_size.y / 2.f ) - 100.f ) );
    _sound_effect_volume_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    const auto sound_effect_label = std::make_shared< Label >( *get_context()._fonts, "Sound Effect Volume", 24.f );
    sound_effect_label->setPosition( _sound_effect_volume_button->getPosition() - sf::Vector2f( 0, 25.f ) );
    sound_effect_label->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    _music_volume_button->setPosition( _sound_effect_volume_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    _music_volume_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    const auto music_label = std::make_shared< Label >( *get_context()._fonts, "Music Volume", 24.f );
    music_label->setPosition( _music_volume_button->getPosition() - sf::Vector2f( 0, 25.f ) );
    music_label->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    _network_button->setPosition( _music_volume_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    _network_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    const auto network_label = std::make_shared< Label >( *get_context()._fonts, "Enable Network", 24.f );
    network_label->setPosition( _network_button->getPosition() - sf::Vector2f( 0, 25.f ) );
    network_label->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    back_button->setPosition( _network_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    back_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    _container.pack( sound_effect_label );
    _container.pack( _sound_effect_volume_button );
    _container.pack( music_label );
    _container.pack( _music_volume_button );
    _container.pack( network_label );
    _container.pack( _network_button );
    _container.pack( back_button );

    _settings_text.setString( "Settings" );
    _settings_text.setCharacterSize( 64.f );
    Utility::center_origin( _settings_text );
    _settings_text.setPosition( sf::Vector2f( view_size.x / 2.f, 200.f ) );
}

/**
 * Visually display the various components that make up the Settings state
 */
void State_Settings::draw()
{
    sf::RenderWindow& window = *get_context()._window;
    window.setView( window.getDefaultView() );
    window.draw( _settings_text );
    window.draw( _container );
}

/**
 * Realtime update the various components
 * @param dt The clock time
 * @return always true
 */
bool State_Settings::update( const sf::Time dt )
{
    ( void ) dt;
    _music_volume_button->set_text( std::to_string( static_cast< int >( get_context()._music->get_volume() ) ) );
    _sound_effect_volume_button->set_text( std::to_string( static_cast< int >( get_context()._sounds->get_volume() ) ) );
    return true;
}

/**
 * Event handler for the current state
 * @param event The event that has been called
 * @return always false
 */
bool State_Settings::handle_event( const sf::Event& event )
{
    bool is_setting_volume = false;

    if ( _sound_effect_volume_button->is_active() )
    {
        is_setting_volume = true;
        if ( const auto *keyReleased = event.getIf<sf::Event::KeyReleased>() )
        {
            if ( keyReleased->scancode == sf::Keyboard::Scancode::Enter )
            {
                _sound_effect_volume_button->deactivate();
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Left || keyReleased->scancode == sf::Keyboard::Scancode::Down )
            {
                change_sound_effect_volume( -5.f );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Right || keyReleased->scancode == sf::Keyboard::Scancode::Up )
            {
                change_sound_effect_volume( 5.f );
            }
        }
    }
    if ( _music_volume_button->is_active() )
    {
        is_setting_volume = true;
        if ( const auto *keyReleased = event.getIf<sf::Event::KeyReleased>() )
        {
            if ( keyReleased->scancode == sf::Keyboard::Scancode::Enter )
            {
                _music_volume_button->deactivate();
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Left || keyReleased->scancode == sf::Keyboard::Scancode::Down )
            {
                change_music_volume( -5.f );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Right || keyReleased->scancode == sf::Keyboard::Scancode::Up )
            {
                change_music_volume( 5.f );
            }
        }
    }
    if ( _sound_effect_volume_button->is_selected() && !is_setting_volume )
    {
        if ( const auto *keyReleased = event.getIf<sf::Event::KeyReleased>() )
        {
            if ( keyReleased->scancode == sf::Keyboard::Scancode::M )
            {
                float vol = get_context()._sounds->get_volume();
                if ( vol > 0.f )
                {
                    tmp_sound_effect_vol = get_context()._sounds->get_volume();
                    vol = 0.f;
                } else
                {
                    vol = tmp_sound_effect_vol;
                }
                get_context()._sounds->set_volume( vol );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Left )
            {
                change_sound_effect_volume( -5.f );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Right )
            {
                change_sound_effect_volume( 5.f );
            }
        }
    }
    if ( _music_volume_button->is_selected() && !is_setting_volume )
    {
        if ( const auto *keyReleased = event.getIf<sf::Event::KeyReleased>() )
        {
            if ( keyReleased->scancode == sf::Keyboard::Scancode::M )
            {
                float vol = get_context()._music->get_volume();
                if ( vol > 0.f )
                {
                    tmp_music_vol = get_context()._music->get_volume();
                    vol = 0.f;
                } else
                {
                    vol = tmp_music_vol;
                }
                get_context()._music->set_volume( vol );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Left )
            {
                change_music_volume( -5.f );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Right )
            {
                change_music_volume( 5.f );
            }
        }
    }

    if ( !is_setting_volume )
    {
        _container.handle_event( event );
        if ( const auto *keyReleased = event.getIf<sf::Event::KeyReleased>() )
        {
            if ( keyReleased->scancode == sf::Keyboard::Scancode::Escape )
            {
                request_stack_pop();
            }
        }
    }
    return false;
}

/**
 * Function to change the sound effect volume
 * @param val The value that we wish to increase or decrease the volume with
 */
void State_Settings::change_sound_effect_volume( const float val ) const
{
    float vol = get_context()._sounds->get_volume() + val;
    if ( vol < 0.f )
    {
        vol = 100.f;
    }
    if ( vol > 100.f )
    {
        vol = 0.f;
    }
    get_context()._sounds->set_volume( vol );
}

/**
 * Function to change the music volume
 * @param val The value we wish to increase or decrease the volume with
 */
void State_Settings::change_music_volume( const float val ) const
{
    float vol = get_context()._music->get_volume() + val;
    if ( vol < 0.f )
    {
        vol = 100.f;
    } else if ( vol > 100.f )
    {
        vol = 0.f;
    }
    get_context()._music->set_volume( vol );
}
