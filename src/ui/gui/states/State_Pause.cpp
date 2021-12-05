#include "State_Pause.hpp"

#include "../Utility.hpp"
#include "../../Resource_Holder.hpp"
#include "../Music_Player.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sokoban::ui::gui;

State_Pause::State_Pause( State_Stack &stack, State::Context context )
        : State( stack, context )
{
    sf::Texture &texture = context._textures->get( Textures::Title_Screen );
    sf::Font &font = context._fonts->get( Fonts::Rampart_One );
    sf::Vector2f view_size = context._window->getView().getSize();

    _background_sprite.setTexture( texture );
    Utility::center_origin( _background_sprite );
    _background_sprite.setPosition( view_size / 2.f );

    _paused_text.setFont( font );
    _paused_text.setString( "Paused" );
    _paused_text.setCharacterSize( 64.f );
    Utility::center_origin( _paused_text );
    _paused_text.setPosition( view_size.x / 2.f, view_size.y / 2.f - 100.f );

    _back_text.setFont( font );
    _back_text.setString( "Back" );
    _back_text.setCharacterSize( 32.f );
    Utility::center_origin( _back_text );
    _back_text.setPosition( view_size / 2.f );
}

void State_Pause::draw()
{
    sf::RenderWindow &window = *get_context()._window;
    window.setView( window.getDefaultView() );
    window.draw( _paused_text );
    window.draw( _back_text );
}

bool State_Pause::update( sf::Time dt )
{
    return true;
}

bool State_Pause::handle_event( const sf::Event &event )
{
    if( event.type == sf::Event::KeyPressed )
    {
        if( event.key.code == sf::Keyboard::Escape )
        {
            request_stack_pop();
        }
    }
    return false;
}
