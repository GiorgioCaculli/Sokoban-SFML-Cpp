#include "State_Title.hpp"

#include <util/logger/Logger.hpp>
#include "../Utility.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;
using namespace util;

/**
 * Default constructor for the Title state
 * @param stack The stack containing the various states
 * @param context The context containing the various resources
 */
State_Title::State_Title( State_Stack &stack, State::Context context )
        : State( stack, context )
        , _text()
        , _title_text()
        , _show_text( true )
        , _text_effect_time( sf::Time::Zero )
{
    Logger logger( "State Title", "sokoban.log", true );
    logger.log( Logger::Level::DEBUG, "Initializing Title Screen" );

    logger.log( Logger::Level::DEBUG, "Loading Title Screen Texture" );
    _background_sprite.setTexture( context._textures->get( Textures::Title_Screen ) );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( context._window->getView().getSize() / 2.f );

    logger.log( Logger::Level::DEBUG, "Loading Title Screen Text" );

    _title_text.setFont( context._fonts->get( Fonts::Kodomo_Rounded ) );
    _title_text.setString( L"そこばん" );
    Utility::center_origin( _title_text );
    sf::Vector2f pos( context._window->getView().getSize() / 2.f );
    _title_text.setPosition( pos.x / 1.5f, 10.f );
    _title_text.setCharacterSize( 8 * 24 );
    _title_text.setFillColor( sf::Color::Cyan );

    _title_sub_text.setFont( context._fonts->get( Fonts::Kodomo_Rounded ) );
    _title_sub_text.setString( "Sokoban" );
    Utility::center_origin( _title_sub_text );
    _title_sub_text.setPosition( pos.x / 1.2f, _title_text.getPosition().y + 200.f );
    _title_sub_text.setCharacterSize( 4 * 24 );
    _title_sub_text.setFillColor( sf::Color::Cyan );

    _text.setFont( context._fonts->get( Fonts::Rampart_One ) );
    _text.setString( "Press any key to start" );
    Utility::center_origin( _text );
    _text.setPosition( pos.x, pos.y + 150.f );
    _text.setCharacterSize( 32 );
}

/**
 * Visually display the various components within the state
 */
void State_Title::draw()
{
    sf::RenderWindow &window = *get_context()._window;
    window.draw( _background_sprite );
    window.draw( _title_text );
    window.draw( _title_sub_text );
    if( _show_text )
    {
        window.draw( _text );
    }
}

/**
 * Realtime update each component
 * @param dt The clock time
 * @return always true
 */
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

/**
 * Event handler for the current state
 * @param event The event to manage
 * @return always true
 */
bool State_Title::handle_event( const sf::Event &event )
{
    if( event.type == sf::Event::KeyReleased )
    {
        request_stack_pop();
        request_stack_push( States::Menu );
    }
    return true;
}
