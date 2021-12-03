#include "State_Title.hpp"

#include "../Utility.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;

State_Title::State_Title( State_Stack &stack, State::Context context )
        : State( stack, context )
        , _text()
        , _show_text( true )
        , _text_effect_time( sf::Time::Zero )
{
    _background_sprite.setTexture( context._textures->get( Textures::TitleScreen ) );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( context._window->getView().getSize() / 2.f );
    _text.setFont( context._fonts->get( Fonts::Main ) );
    _text.setString( L"Press any key to start é" );
    Utility::center_origin( _text );
    _text.setPosition( context._window->getView().getSize() / 2.f );
}

void State_Title::draw()
{
    sf::RenderWindow &window = *get_context()._window;
    window.draw( _background_sprite );
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
    if( event.type == sf::Event::KeyPressed )
    {
        request_stack_pop();
        request_stack_push( States::Menu );
    }
    return true;
}
