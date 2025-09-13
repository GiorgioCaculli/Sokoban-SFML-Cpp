#include <gui/states/State_Menu.hpp>

#include <gui/components/Button.hpp>
#include <gui/Utility.hpp>
#include <ui/Resource_Holder.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the Menu state
 * @param stack The stack containing the various states
 * @param context The context meant to access all the resources available
 */
State_Menu::State_Menu( State_Stack& stack, Context context )
    : State( stack, context )
    , _background_sprite( context._textures->get( Textures::Title_Screen ) )
{
    const auto window_view_size = context._window->getView().getSize();
    //sf::Font &font = context._fonts->get( Fonts::Rampart_One );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( window_view_size / 2.f );

    _play_button = std::make_shared< Button >( context );
    _play_button->set_text( "Play" );
    _play_button->set_callback( [ this ]
    {
        request_stack_pop();
        request_stack_push( States::Game );
    } );

    _settings_button = std::make_shared< Button >( context );
    _settings_button->set_text( "Settings" );
    _settings_button->set_callback( [ this ]
    {
        request_stack_push( States::Settings );
    } );

    _exit_button = std::make_shared< Button >( context );
    _exit_button->set_text( "Exit" );
    _exit_button->set_callback( [ this ]
    {
        get_context()._window->close();
    } );

    _settings_button->setPosition( window_view_size / 2.f );
    _settings_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );
    _play_button->setPosition( _settings_button->getPosition() - sf::Vector2f( 0, 100.f ) );
    _play_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );
    _exit_button->setPosition( _settings_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    _exit_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    _container.pack( _play_button );
    _container.pack( _settings_button );
    _container.pack( _exit_button );
}

/**
 * Visually draw the various components and entities with the state
 */
void State_Menu::draw()
{
    sf::RenderWindow& window = *get_context()._window;

    window.setView( window.getDefaultView() );
    window.draw( _background_sprite );
    window.draw( _container );
}

/**
 * Realtime update the various components
 * @param dt The clock time
 * @return always true
 */
bool State_Menu::update( const sf::Time dt )
{
    ( void ) dt;
    return true;
}

/**
 * Event handler for the Menu container
 * @param event The event that has been called
 * @return always false
 */
bool State_Menu::handle_event( const sf::Event& event )
{
    return handle_keyboard_events( event ) || handle_mouse_events( event );
}

bool State_Menu::handle_keyboard_events( const sf::Event& event )
{
    _container.handle_event( event );
    return false;
}

bool State_Menu::handle_mouse_events( const sf::Event& event )
{
    const auto context = get_context();
    context._mouse->pressing( event, sf::Mouse::Button::Left, _play_button, [ this ]
    {
        request_stack_pop();
        request_stack_push( States::Game );
        return false;
    } );
    context._mouse->pressing( event, sf::Mouse::Button::Right, _settings_button, [ this ]
    {
        request_stack_push( States::Settings );
        return true;
    } );
    context._mouse->pressing( event, sf::Mouse::Button::Left, _exit_button, [ this ]
    {
        get_context()._window->close();
        return true;
    } );
    return false;
}
