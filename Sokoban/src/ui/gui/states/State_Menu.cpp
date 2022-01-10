#include <gzc/games/sokoban/ui/gui/sfml/states/State_Menu.hpp>

#include <gzc/games/sokoban/ui/gui/sfml/components/Button.hpp>
#include <gzc/games/sokoban/ui/gui/sfml/Utility.hpp>
#include <gzc/games/sokoban/ui/Resource_Holder.hpp>
#include <gzc/games/sokoban/ui/gui/sfml/Music_Player.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <cmath>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the Menu state
 * @param stack The stack containing the various states
 * @param context The context meant to access all the resources available
 */
State_Menu::State_Menu( State_Stack &stack, State::Context context )
        : State( stack, context )
        , _container()
{
    sf::Texture &texture = context._textures->get( Textures::Title_Screen );
    //sf::Font &font = context._fonts->get( Fonts::Rampart_One );

    _background_sprite.setTexture( texture );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( context._window->getView().getSize() / 2.f );

    auto play_button = std::make_shared< Button >( context );
    play_button->set_text( "Play" );
    play_button->set_callback( [ this ] ()
    {
        request_stack_pop();
        request_stack_push( States::Game );
    });

    auto settings_button = std::make_shared< Button >( context );
    settings_button->set_text( "Settings" );
    settings_button->set_callback( [ this ] ()
    {
        request_stack_push( States::Settings );
    });

    auto exit_button = std::make_shared< Button >( context );
    exit_button->set_text( "Exit" );
    exit_button->set_callback( [ this ] ()
    {
        get_context()._window->close();
    });

    settings_button->setPosition( context._window->getView().getSize() / 2.f );
    settings_button->setOrigin( 100.f, 25.f );
    play_button->setPosition( settings_button->getPosition() - sf::Vector2f( 0, 100.f ) );
    play_button->setOrigin( 100.f, 25.f );
    exit_button->setPosition( settings_button->getPosition() + sf::Vector2f( 0, 100.f ) );
    exit_button->setOrigin( 100.f, 25.f );

    _container.pack( play_button );
    _container.pack( settings_button );
    _container.pack( exit_button );
}

/**
 * Visually draw the various components and entities with the state
 */
void State_Menu::draw()
{
    sf::RenderWindow &window = *get_context()._window;

    window.setView( window.getDefaultView() );
    window.draw( _background_sprite );
    window.draw( _container );
}

/**
 * Realtime update the various components
 * @param dt The clock time
 * @return always true
 */
bool State_Menu::update( sf::Time dt )
{
    (void) dt;
    return true;
}

/**
 * Event handler for the Menu container
 * @param event The event that has been called
 * @return always false
 */
bool State_Menu::handle_event( const sf::Event &event )
{
    _container.handle_event( event );
    return false;
}
