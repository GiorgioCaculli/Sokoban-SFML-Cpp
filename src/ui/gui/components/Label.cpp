#include "Label.hpp"

#include "../Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

Label::Label( const std::string &text, const sokoban::ui::Font_Holder &fonts, float character_size )
: _text( text, fonts.get( Fonts::Rampart_One ), character_size )
{
}

bool Label::is_selectable() const
{
    return false;
}

void Label::set_text( const std::string &text )
{
    _text.setString( text );
}

void Label::handle_event( const sf::Event &event )
{
}

void Label::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( _text, states );
}
