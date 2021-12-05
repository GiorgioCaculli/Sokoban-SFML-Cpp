#include "Button.hpp"

#include "../Utility.hpp"
#include "../Sound_Player.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

Button::Button( State::Context context )
: _callback()
, _sprite( context._textures->get( Textures::Button ) )
, _text( "", context._fonts->get( Fonts::Rampart_One ) )
, _is_toggled( false )
, _sounds( *context._sounds )
{
    change_texture( Normal );

    sf::FloatRect bounds = _sprite.getLocalBounds();
    _text.setPosition( bounds.width / 2.f, bounds.height / 2.f );
}

void Button::set_callback( Button::Callback callback )
{
    _callback = std::move( callback );
}

void Button::set_text( const std::string &text )
{
    _text.setString( text );
    Utility::center_origin( _text );
}

void Button::set_toggle( bool flag )
{
    _is_toggled = flag;
}

bool Button::is_selectable() const
{
    return true;
}

void Button::select()
{
    Component::select();

    change_texture( Selected );
    _sounds.play( Sound_Effect::Button_Click_02 );
}

void Button::deselect()
{
    Component::deselect();

    change_texture( Normal );
}

void Button::activate()
{
    Component::activate();
    if( _is_toggled )
    {
        change_texture( Pressed );
    }
    if( _callback )
    {
        _callback();
    }
    if( !_is_toggled )
    {
        deactivate();
    }
    _sounds.play( Sound_Effect::Button_Click_01 );
}

void Button::deactivate()
{
    Component::deactivate();

    if( _is_toggled )
    {
        if( is_selected() )
        {
            change_texture( Selected );
        }
        else
        {
            change_texture( Normal );
        }
    }
}

void Button::handle_event( const sf::Event &event )
{
}

void Button::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( _sprite, states );
    target.draw( _text, states );
}

void Button::change_texture( Button::Type button_type )
{
    sf::IntRect texture_rect( 0, 50 * button_type, 200, 50 );
    _sprite.setTextureRect( texture_rect );
}
