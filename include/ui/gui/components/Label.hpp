#ifndef SOKOBAN_LABEL_HPP
#define SOKOBAN_LABEL_HPP

#include <ui/gui/components/Component.hpp>
#include <ui/gui/Resource_Identifiers.hpp>
#include <ui/Resource_Holder.hpp>

#include <SFML/Graphics/Text.hpp>


namespace sokoban::ui::gui
{
    class Label final
            : public Component
    {
    public:
        /** Shared pointer meant to define the component as a Label */
        typedef std::shared_ptr< Label > Ptr;

        Label( const Font_Holder& fonts, const std::string& text, unsigned int character_size );

        bool is_selectable() const override;

        void set_text( const std::string& text );

        void handle_event( const sf::Event& event ) override;

    private:
        sf::Text _text; /** The text meant to be displayed */
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
    };
}


#endif //SOKOBAN_LABEL_HPP
