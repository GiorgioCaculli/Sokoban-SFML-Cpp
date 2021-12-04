#include "State_Title.hpp"

#include "../../../util/Logger.hpp"
#include "../Utility.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;
using namespace sokoban::util;

State_Title::State_Title( State_Stack &stack, State::Context context )
        : State( stack, context )
        , _text()
        , _title_text()
        , _show_text( true )
        , _text_effect_time( sf::Time::Zero )
{
    Logger::log( LoggerLevel::DEBUG, "Initializing Title Screen" );

    Logger::log( LoggerLevel::DEBUG, "Loading Title Screen Texture" );
    _background_sprite.setTexture( context._textures->get( Textures::Title_Screen ) );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( context._window->getView().getSize() / 2.f );

    Logger::log( LoggerLevel::DEBUG, "Loading Title Screen Text" );

    _title_text.setFont( context._fonts->get( Fonts::Kodomo_Rounded ) );
    _title_text.setString( L"そこばん" );
    Utility::center_origin( _title_text );
    sf::Vector2f pos( context._window->getView().getSize() / 2.f );
    _title_text.setPosition( pos.x / 1.5f, pos.y / 1.5f );
    _title_text.setCharacterSize( 8 * 24 );

    _text.setFont( context._fonts->get( Fonts::Rampart_One ) );
    _text.setString( "Press any key to start" );
    Utility::center_origin( _text );
    _text.setPosition( pos.x, pos.y + 150.f );
    _text.setCharacterSize( 32 );
}

void State_Title::draw()
{
    sf::RenderWindow &window = *get_context()._window;
    window.draw( _background_sprite );
    window.draw( _title_text );
    if( _show_text )
    {
        window.draw( _text );
    }
}

bool State_Title::update( sf::Time dt )
{
    _text_effect_time += dt;
    if( _text_effect_time >= sf::seconds( 0.5f ) )
    {
        _show_text = !_show_text;
        _text_effect_time = sf::Time::Zero;
    }
    return true;
}

bool State_Title::handle_event( const sf::Event &event )
{
    if( event.type == sf::Event::KeyReleased )
    {
        request_stack_pop();
        request_stack_push( States::Menu );
    }
    return true;
}
