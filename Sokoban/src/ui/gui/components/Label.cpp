#include <gzc/games/sokoban/ui/gui/sfml/components/Label.hpp>

#include <gzc/games/sokoban/ui/gui/sfml/Utility.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

/**
 * Constructor for the Label component
 * @param text The text meant to be shown
 * @param fonts The font it should be characterized in
 * @param character_size The character size
 */
Label::Label( const std::string &text, const sokoban::ui::Font_Holder &fonts, float character_size )
: _text( text, fonts.get( Fonts::Rampart_One ), character_size )
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
void Label::set_text( const std::string &text )
{
    _text.setString( text );
}

/**
 * Empty since a label does not execute any sort of action by default
 * @param event None
 */
void Label::handle_event( const sf::Event &event )
{
    (void)event;
}

/**
 * Function that will display the label visually
 */
void Label::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( _text, states );
}
