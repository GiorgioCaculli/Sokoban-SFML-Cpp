#include <ui/gui/components/Label.hpp>

#include <ui/gui/Utility.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

/**
 * Constructor for the Label component
 * @param fonts The font it should be characterized in
 * @param text The text meant to be shown
 * @param character_size The character size
 */
Label::Label( const sokoban::ui::Font_Holder& fonts, const std::string& text, const unsigned int character_size )
    : _text( fonts.get( Fonts::Rampart_One ), text, character_size )
{
}

/**
 * Make the label not selectable
 * @return false since a label is just text
 */
bool Label::is_selectable() const
{
    return false;
}

/**
 * Setter for the text in case of changes
 * @param text The text meant to be shown
 */
void Label::set_text( const std::string& text )
{
    _text.setString( text );
}

/**
 * Empty since a label does not execute any sort of action by default
 * @param event None
 */
void Label::handle_event( const sf::Event& event )
{
    ( void ) event;
}

/**
 * Function that will display the label visually
 */
void Label::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( _text, states );
}
