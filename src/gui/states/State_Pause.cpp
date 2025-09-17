#include <gui/states/State_Pause.hpp>

#include <gui/components/Button.hpp>
#include <gui/Utility.hpp>
#include <ui/Resource_Holder.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the Pause state
 * @param stack The stack containing the various states
 * @param context The context containing the various resources
 */
State_Pause::State_Pause( State_Stack& stack, const Context& context )
    : State( stack, context )
    , _background_sprite( context._textures->get( Textures::ID::Title_Screen ) )
    , _paused_text( context._fonts->get( Fonts::ID::Rampart_One ) )
{
    const sf::Vector2f view_size = context._window->getView().getSize();

    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( view_size / 2.f );

    _paused_text.setString( "Paused" );
    _paused_text.setCharacterSize( 64.f );
    Utility::center_origin( _paused_text );
    _paused_text.setPosition( sf::Vector2f( view_size.x / 2.f, view_size.y / 2.f - 200.f ) );

    _resume_button = std::make_shared< Button >( context );
    _resume_button->set_text( "Resume" );
    _resume_button->set_callback( [ this ]
    {
        _resume_button_callback();
    } );

    _settings_button = std::make_shared< Button >( context );
    _settings_button->set_text( "Settings" );
    _settings_button->set_callback( [ this ]
    {
        _settings_button_callback();
    } );

    _back_to_main_menu_button = std::make_shared< Button >( context );
    _back_to_main_menu_button->set_text( "Main Menu" );
    _back_to_main_menu_button->set_callback( [ this ]
    {
        _back_to_main_menu_button_callback();
    } );

    _settings_button->setPosition( context._window->getView().getSize() / 2.f );
    _settings_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );
    _resume_button->setPosition( _settings_button->getPosition() - sf::Vector2f( 0, 100.f ) );
    _resume_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );
    _back_to_main_menu_button->setPosition( _settings_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    _back_to_main_menu_button->setOrigin( sf::Vector2f( 100.f, 25.f ) );

    _container.pack( _resume_button );
    _container.pack( _settings_button );
    _container.pack( _back_to_main_menu_button );
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
bool State_Pause::update( const sf::Time dt )
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
    return handle_keyboard_events( event ) || handle_mouse_events( event );
}

bool State_Pause::handle_keyboard_events( const sf::Event& event )
{
    const auto context = get_context();
    _container.handle_event( event );
    context._keyboard->releasing( event, { sf::Keyboard::Scancode::Escape }, [ this ]
    {
        request_stack_pop();
        return true;
    } );
    return false;
}

bool State_Pause::handle_mouse_events( const sf::Event& event )
{
    const auto context = get_context();
    context._mouse->pressing( event, sf::Mouse::Button::Left, _resume_button, [ this ]
    {
        return _resume_button_callback();
    } );
    context._mouse->pressing( event, sf::Mouse::Button::Right, _settings_button, [ this ]
    {
        return _settings_button_callback();
    } );
    context._mouse->pressing( event, sf::Mouse::Button::Middle, _back_to_main_menu_button, [ this ]
    {
        return _back_to_main_menu_button_callback();
    } );
    return false;
}

bool State_Pause::_resume_button_callback() const
{
    request_stack_pop();
    return true;
}

bool State_Pause::_settings_button_callback() const
{
    request_stack_push( States::ID::Settings );
    return true;
}

bool State_Pause::_back_to_main_menu_button_callback() const
{
    request_stack_pop();
    request_stack_pop();
    request_stack_push( States::ID::Menu );
    return true;
}
