#include "State_Menu.hpp"

#include "../Utility.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

using namespace sokoban::ui::gui;

State_Menu::State_Menu( State_Stack &stack, State::Context context )
        : State( stack, context )
        , _options()
        , _option_index( 0 )
{
    sf::Texture &texture = context._textures->get( Textures::TitleScreen );
    sf::Font &font = context._fonts->get( Fonts::Main );
    _background_sprite.setTexture( texture );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( context._window->getView().getSize() / 2.f );

    sf::Text play_option;
    play_option.setFont( font );
    play_option.setString( "Play" );
    Utility::center_origin( play_option );
    play_option.setPosition( context._window->getView().getSize() / 2.f );
    _options.push_back( play_option );

    sf::Text exit_option;
    exit_option.setFont( font );
    exit_option.setString( "Exit" );
    Utility::center_origin( exit_option );
    exit_option.setPosition( play_option.getPosition() + sf::Vector2f( 0.f, 30.f  ) );
    _options.push_back( exit_option );

    update_option_text();
}

void State_Menu::draw()
{
    sf::RenderWindow &window = *get_context()._window;

    window.setView( window.getDefaultView() );
    window.draw( _background_sprite );
    for( const sf::Text &text : _options )
    {
        window.draw( text );
    }
}

bool State_Menu::update( sf::Time dt )
{
    return true;
}

bool State_Menu::handle_event( const sf::Event &event )
{
    if( event.type != sf::Event::KeyPressed )
    {
        return false;
    }
    if( event.key.code == sf::Keyboard::Return )
    {
        if( _option_index == Play )
        {
            request_stack_pop();
            request_stack_push( States::Game );
        }
        else if( _option_index == Exit )
        {
            request_stack_pop();
        }
    }
    else if( event.key.code == sf::Keyboard::Up )
    {
        if( _option_index > 0 )
        {
            _option_index--;
        }
        else
        {
            _option_index = _options.size() - 1;
        }
        update_option_text();
    }
    else if( event.key.code == sf::Keyboard::Down )
    {
        if( _option_index < _options.size() - 1 )
        {
            _option_index++;
        }
        else
        {
            _option_index = 0;
        }
        update_option_text();
    }
    return true;
}

void State_Menu::update_option_text()
{
    if( _options.empty() )
    {
        return;
    }
    for( sf::Text &text : _options )
    {
        text.setFillColor( sf::Color::White );
    }
    _options[ _option_index ].setFillColor( sf::Color::Red );
    std::string option = _options[ _option_index ].getString();
    std::cout << option << std::endl;
}
