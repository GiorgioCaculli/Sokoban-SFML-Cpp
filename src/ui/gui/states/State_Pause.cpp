#include <ui/gui/states/State_Pause.hpp>

#include <ui/gui/components/Button.hpp>
#include <ui/gui/Utility.hpp>
#include <ui/Resource_Holder.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <cmath>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the Pause state
 * @param stack The stack containing the various states
 * @param context The context containing the various resources
 */
State_Pause::State_Pause( State_Stack& stack, State::Context context )
    : State( stack, context )
{
    sf::Texture& texture = context._textures->get( Textures::Title_Screen );
    sf::Font& font = context._fonts->get( Fonts::Rampart_One );
    sf::Vector2f view_size = context._window->getView().getSize();

    _background_sprite.setTexture( texture );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( view_size / 2.f );

    _paused_text.setFont( font );
    _paused_text.setString( "Paused" );
    _paused_text.setCharacterSize( 64.f );
    Utility::center_origin( _paused_text );
    _paused_text.setPosition( sf::Vector2f( view_size.x / 2.f, view_size.y / 2.f - 200.f ) );

    auto resume_button = std::make_shared< Button >( context );
    resume_button->set_text( "Resume" );
    resume_button->set_callback( [ this ]()
    {
        request_stack_pop();
    } );

    auto settings_button = std::make_shared< Button >( context );
    settings_button->set_text( "Settings" );
    settings_button->set_callback( [ this ]()
    {
        request_stack_push( States::Settings );
    } );

    auto back_to_main_menu_button = std::make_shared< Button >( context );
    back_to_main_menu_button->set_text( "Main Menu" );
    back_to_main_menu_button->set_callback( [ this ]()
    {
        request_stack_pop();
        request_stack_pop();
        request_stack_push( States::Menu );
    } );

    settings_button->setPosition( context._window->getView().getSize() / 2.f );
    settings_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );
    resume_button->setPosition( settings_button->getPosition() - sf::Vector2f( 0, 100.f ) );
    resume_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );
    back_to_main_menu_button->setPosition( settings_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    back_to_main_menu_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    _container.pack( resume_button );
    _container.pack( settings_button );
    _container.pack( back_to_main_menu_button );
}

/**
 * Visually display the various components that make up the state
 */
void State_Pause::draw()
{
    sf::RenderWindow& window = *get_context()._window;
    window.setView( window.getDefaultView() );
    window.draw( _paused_text );
    window.draw( _container );
}

/**
 * Realtime update the various components
 * @param dt The clock time
 * @return always true
 */
bool State_Pause::update( sf::Time dt )
{
    ( void ) dt;
    return true;
}

/**
 * Event handler for the current pause state
 * @param event The event that has been called
 * @return always false
 */
bool State_Pause::handle_event( const sf::Event& event )
{
    _container.handle_event( event );
    if ( const auto *keyPressed = event.getIf<sf::Event::KeyPressed>() )
    {
        if ( keyPressed->scancode == sf::Keyboard::Scancode::Escape )
        {
            request_stack_pop();
        }
    }
    return false;
}
