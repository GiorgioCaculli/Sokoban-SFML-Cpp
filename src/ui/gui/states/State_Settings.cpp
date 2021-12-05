#include "State_Settings.hpp"

#include "../components/Button.hpp"
#include "../Utility.hpp"
#include "../../Resource_Holder.hpp"
#include "../Music_Player.hpp"
#include "../Sound_Player.hpp"
#include "../components/Label.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <cmath>

using namespace sokoban::ui::gui;

namespace
{
    float tmp_music_vol;
    float tmp_sound_effect_vol;
}

State_Settings::State_Settings( State_Stack &stack, Context context )
        : State( stack, context )
{
    sf::Texture &texture = context._textures->get( Textures::Title_Screen );
    sf::Font &font = context._fonts->get( Fonts::Rampart_One );
    sf::Vector2f view_size = context._window->getView().getSize();

    _background_sprite.setTexture( texture );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( view_size / 2.f );

    _music_volume_button = std::make_shared< Button >( context );
    _music_volume_button->set_text( std::to_string( ( int ) get_context()._music->get_volume() ) );
    _music_volume_button->set_toggle( true );

    _sound_effect_volume_button = std::make_shared< Button >( context );
    _sound_effect_volume_button->set_text( std::to_string( ( int ) get_context()._sounds->get_volume() ) );
    _sound_effect_volume_button->set_toggle( true );

    auto back_button = std::make_shared< Button >( context );
    back_button->set_text( "Back" );
    back_button->set_callback( [ this ] ()
    {
        request_stack_pop();
    });

    _sound_effect_volume_button->setPosition( context._window->getView().getSize() / 2.f );
    _sound_effect_volume_button->setOrigin( 100.f, 25.f );

    auto sound_effect_label = std::make_shared< Label >( "Sound Effect Volume", *get_context()._fonts, 24.f );
    sound_effect_label->setPosition( _sound_effect_volume_button->getPosition() - sf::Vector2f( 0, 25.f ) );
    sound_effect_label->setOrigin( 100.f, 25.f );

    _music_volume_button->setPosition( _sound_effect_volume_button->getPosition() - sf::Vector2f( 0, 100.f ) );
    _music_volume_button->setOrigin( 100.f, 25.f );

    auto music_label= std::make_shared< Label >( "Music Volume", *get_context()._fonts, 24.f );
    music_label->setPosition( _music_volume_button->getPosition() - sf::Vector2f( 0, 25.f ) );
    music_label->setOrigin( 100.f, 25.f );

    back_button->setPosition( _sound_effect_volume_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    back_button->setOrigin( 100.f, 25.f );

    _container.pack( _music_volume_button );
    _container.pack( music_label );
    _container.pack( _sound_effect_volume_button );
    _container.pack( sound_effect_label );
    _container.pack( back_button );

    _settings_text.setFont( font );
    _settings_text.setString( "Settings" );
    _settings_text.setCharacterSize( 64.f );
    Utility::center_origin( _settings_text );
    _settings_text.setPosition( view_size.x / 2.f, 200.f );
}

void State_Settings::draw()
{
    sf::RenderWindow &window = *get_context()._window;
    window.setView( window.getDefaultView() );
    window.draw( _background_sprite );
    window.draw( _settings_text );
    window.draw( _container );
}

bool State_Settings::update( sf::Time dt )
{
    _music_volume_button->set_text( std::to_string( ( int ) get_context()._music->get_volume() ) );
    _sound_effect_volume_button->set_text( std::to_string( ( int ) get_context()._sounds->get_volume() ) );
    return true;
}

bool State_Settings::handle_event( const sf::Event &event )
{
    bool is_setting_volume = false;

    if( _sound_effect_volume_button->is_active() )
    {
        is_setting_volume = true;
        if( event.type == sf::Event::KeyReleased )
        {
            if( event.key.code == sf::Keyboard::Enter )
            {
                _sound_effect_volume_button->deactivate();
            }
            else if( event.key.code == sf::Keyboard::Left )
            {
                float vol = get_context()._sounds->get_volume() - 5;
                if( vol < 0.f )
                {
                    vol = 100.f;
                }
                get_context()._sounds->set_volume( vol );
            }
            else if( event.key.code == sf::Keyboard::Right )
            {
                float vol = get_context()._sounds->get_volume() + 5;
                if( vol > 100.f )
                {
                    vol = 0.f;
                }
                get_context()._sounds->set_volume( vol );
            }
            else if( event.key.code == sf::Keyboard::Space )
            {
                float vol = get_context()._sounds->get_volume();
                tmp_sound_effect_vol = vol;
                if( vol > 0.f )
                {
                    vol = 0.f;
                }
                else
                {
                    vol = tmp_sound_effect_vol;
                }
                get_context()._sounds->set_volume( vol );
                _sound_effect_volume_button->deactivate();
            }
        }
    }
    if( _music_volume_button->is_active() )
    {
        is_setting_volume = true;
        if( event.type == sf::Event::KeyReleased )
        {
            if( event.key.code == sf::Keyboard::Enter )
            {
                _music_volume_button->deactivate();
            }
            else if( event.key.code == sf::Keyboard::Left )
            {
                float vol = get_context()._music->get_volume() - 5;
                if( vol < 0.f )
                {
                    vol = 100.f;
                }
                get_context()._music->set_volume( vol );
            }
            else if( event.key.code == sf::Keyboard::Right )
            {
                float vol = get_context()._music->get_volume() + 5;
                if( vol > 100.f )
                {
                    vol = 0.f;
                }
                get_context()._music->set_volume( vol );
            }
        }
    }
    if( _sound_effect_volume_button->is_selected() )
    {
        if( event.type == sf::Event::KeyReleased )
        {
            if( event.key.code == sf::Keyboard::M )
            {
                float vol = get_context()._sounds->get_volume();
                if( vol > 0.f )
                {
                    tmp_sound_effect_vol = get_context()._sounds->get_volume();
                    vol = 0.f;
                }
                else
                {
                    vol = tmp_sound_effect_vol;
                }
                get_context()._sounds->set_volume( vol );
            }
        }
    }
    if( _music_volume_button->is_selected() )
    {
        if( event.type == sf::Event::KeyReleased )
        {
            if( event.key.code == sf::Keyboard::M )
            {
                float vol = get_context()._music->get_volume();
                if( vol > 0.f )
                {
                    tmp_music_vol = get_context()._music->get_volume();
                    vol = 0.f;
                }
                else
                {
                    vol = tmp_music_vol;
                }
                get_context()._music->set_volume( vol );
            }
        }
    }

    if( !is_setting_volume )
    {
        _container.handle_event( event );
        if( event.type == sf::Event::KeyReleased )
        {
            if( event.key.code == sf::Keyboard::Escape )
            {
                request_stack_pop();
            }
        }
    }
    return false;
}
