#include <gui/states/State_Settings.hpp>

#include <gui/components/Button.hpp>
#include <gui/Utility.hpp>
#include <ui/Resource_Holder.hpp>
#include <gui/Music_Player.hpp>
#include <gui/Sound_Player.hpp>
#include <gui/components/Label.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the Settings state
 * @param stack The stack containing the various states
 * @param context The context containing the globally accessible resources
 */
State_Settings::State_Settings( State_Stack& stack, Context context )
    : State( stack, context )
      , _background_sprite( context._textures->get( Textures::ID::Title_Screen ) )
      , _settings_text( context._fonts->get( Fonts::ID::Rampart_One ) )
{
    const sf::Vector2f view_size = context._window->getView().getSize();

    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( view_size / 2.f );

    /* Initialize buttons */
    _music_volume_button = std::make_shared< Button >( context );
    _music_volume_button->set_text( std::to_string( static_cast< int >( get_context()._music->get_volume() ) ) );
    _music_volume_button->set_toggle( true );

    _sound_effect_volume_button = std::make_shared< Button >( context );
    _sound_effect_volume_button->
            set_text( std::to_string( static_cast< int >( get_context()._sounds->get_volume() ) ) );
    _sound_effect_volume_button->set_toggle( true );

    _network_button = std::make_shared< Button >( context );
    _network_button->set_text( "Disabled" );
    _network_button->set_toggle( false );

    _back_button = std::make_shared< Button >( context );
    _back_button->set_text( "Back" );
    _back_button->set_callback( [ this ]
    {
        request_stack_pop();
    } );

    /* Position buttons and related labels */
    _sound_effect_volume_button->setPosition( sf::Vector2f( view_size.x / 2.f, view_size.y / 2.f - 100.f ) );
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

    _back_button->setPosition( _network_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    _back_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    _container.pack( sound_effect_label );
    _container.pack( _sound_effect_volume_button );
    _container.pack( music_label );
    _container.pack( _music_volume_button );
    _container.pack( network_label );
    _container.pack( _network_button );
    _container.pack( _back_button );

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
    _sound_effect_volume_button->
            set_text( std::to_string( static_cast< int >( get_context()._sounds->get_volume() ) ) );
    return true;
}

/**
 * Event handler for the current state
 * @param event The event that has been called
 * @return always false
 */
bool State_Settings::handle_event( const sf::Event& event )
{
    return handle_keyboard_events( event ) || handle_mouse_events( event );
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

bool State_Settings::handle_keyboard_events( const sf::Event& event )
{
    bool is_setting_volume = false;
    const auto context = get_context();

    if ( _sound_effect_volume_button->is_active() )
    {
        is_setting_volume = true;
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Enter }, [ this ]
        {
            _sound_effect_volume_button->deactivate();
            return true;
        } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Left, sf::Keyboard::Scancode::Down },
                                      [ this]
                                      {
                                          change_sound_effect_volume( -5.f );
                                          return true;
                                      } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Right, sf::Keyboard::Scancode::Up },
                                      [ this]
                                      {
                                          change_sound_effect_volume( 5.f );
                                          return true;
                                      } );
    }
    if ( _music_volume_button->is_active() )
    {
        is_setting_volume = true;
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Enter }, [ this ]
        {
            _music_volume_button->deactivate();
            return true;
        } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Left, sf::Keyboard::Scancode::Down },
                                      [ this]
                                      {
                                          change_music_volume( -5.f );
                                          return true;
                                      } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Right, sf::Keyboard::Scancode::Up }, [ this]
        {
            change_music_volume( 5.f );
            return true;
        } );
    }
    if ( _sound_effect_volume_button->is_selected() && !is_setting_volume )
    {
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::M }, [ context, this ]
        {
            float vol = context._sounds->get_volume();
            if ( vol > 0.f )
            {
                tmp_sound_effect_vol = context._sounds->get_volume();
                vol = 0.f;
            } else
            {
                vol = tmp_sound_effect_vol;
            }
            context._sounds->set_volume( vol );
            return true;
        } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Left }, [ this ]
        {
            change_sound_effect_volume( -5.f );
            return true;
        } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Right }, [ this ]
        {
            change_sound_effect_volume( 5.f );
            return true;
        } );
    }
    if ( _music_volume_button->is_selected() && !is_setting_volume )
    {
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::M }, [ context, this ]
        {
            float vol = context._music->get_volume();
            if ( vol > 0.f )
            {
                tmp_music_vol = context._music->get_volume();
                vol = 0.f;
            } else
            {
                vol = tmp_music_vol;
            }
            context._music->set_volume( vol );
            return true;
        } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Left }, [ this ]
        {
            change_music_volume( -5.f );
            return true;
        } );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Right }, [ this ]
        {
            change_music_volume( 5.f );
            return true;
        } );
    }

    if ( !is_setting_volume )
    {
        _container.handle_event( event );
        context._keyboard->releasing( event, { sf::Keyboard::Scancode::Escape }, [ this ]
        {
            request_stack_pop();
            return true;
        } );
    }
    return false;
}

bool State_Settings::handle_mouse_events( const sf::Event& event )
{
    const auto context = get_context();
    context._mouse->releasing( event, sf::Mouse::Button::Left, _back_button, [ this ]
    {
        request_stack_pop();
        return true;
    } );
    return false;
}
