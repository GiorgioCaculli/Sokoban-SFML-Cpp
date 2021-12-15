#include "Button.hpp"

#include "../Utility.hpp"
#include "../Sound_Player.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

/**
 * Initializer for the button.
 * Set the default states that characterize the button
 */
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

/**
 * Setter for the type of action a button will execute
 * @param callback The execution
 */
void Button::set_callback( Button::Callback callback )
{
    _callback = std::move( callback );
}

/**
 * Setter for the button's text
 */
void Button::set_text( const std::string &text )
{
    _text.setString( text );
    Utility::center_origin( _text );
}

/**
 * Setter meant to make the button toggleable
 * @param flag Whether it is toggleable or not
 */
void Button::set_toggle( bool flag )
{
    _is_toggled = flag;
}

/**
 * Button meant to determine whether a button is selectable or not.
 */
bool Button::is_selectable() const
{
    return true;
}

/**
 * Function meant to change the texture of a button upon selection
 */
void Button::select()
{
    Component::select();

    change_texture( Selected );
    _sounds.play( Sound_Effect::Button_Click_02 );
}

/**
 * Function meant to deselect a component and change its texture
 */
void Button::deselect()
{
    Component::deselect();

    change_texture( Normal );
}

/**
 * Function meant to make a button active
 */
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

/**
 * Function meant to deactivate an already active button
 */
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

/*
 * Function meant to execute an event
 */
void Button::handle_event( const sf::Event &event )
{
    (void)event;
}

/**
 * Function meant to draw the display the button graphically
 * @param target The target meant to be displayed upon
 * @param states The various preconfigured states that characterise the target
 */
void Button::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( _sprite, states );
    target.draw( _text, states );
}

/**
 * Function meant to change the texture of the button based on its current state
 */
void Button::change_texture( Button::Type button_type )
{
    sf::IntRect texture_rect( 0, 50 * button_type, 200, 50 );
    _sprite.setTextureRect( texture_rect );
}
