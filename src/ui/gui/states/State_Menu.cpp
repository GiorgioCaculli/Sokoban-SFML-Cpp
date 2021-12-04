#include "State_Menu.hpp"

#include "../Button.hpp"
#include "../Utility.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;

State_Menu::State_Menu( State_Stack &stack, State::Context context )
        : State( stack, context )
        , _container()
{
    sf::Texture &texture = context._textures->get( Textures::Title_Screen );
    sf::Font &font = context._fonts->get( Fonts::Rampart_One );

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
        request_stack_pop();
        request_stack_push( States::Settings );
    });

    auto exit_button = std::make_shared< Button >( context );
    exit_button->set_text( "Exit" );
    exit_button->set_callback( [ this ] ()
    {
        get_context()._window->close();
    });

    settings_button->setPosition( context._window->getView().getSize() / 2.f );
    play_button->setPosition( settings_button->getPosition() - sf::Vector2f( 0, 50.f ) );
    exit_button->setPosition( settings_button->getPosition() + sf::Vector2f( 0, 50.f ) );

    _container.pack( play_button );
    _container.pack( settings_button );
    _container.pack( exit_button );
}

void State_Menu::draw()
{
    sf::RenderWindow &window = *get_context()._window;

    window.setView( window.getDefaultView() );
    window.draw( _background_sprite );
    window.draw( _container );
}

bool State_Menu::update( sf::Time dt )
{
    return true;
}

bool State_Menu::handle_event( const sf::Event &event )
{
    _container.handle_event( event );
    return false;
}
