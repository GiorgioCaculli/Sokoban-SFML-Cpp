#ifndef SOKOBAN_LABEL_HPP
#define SOKOBAN_LABEL_HPP

#include "Component.hpp"
#include "../Resource_Identifiers.hpp"
#include "../../Resource_Holder.hpp"

#include <SFML/Graphics/Text.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Label
                    : public Component
            {
            public:
                /** Shared pointer meant to define the component as a Label */
                typedef std::shared_ptr< Label > Ptr;
                Label( const std::string &text, const Font_Holder &fonts, float character_size );
                bool is_selectable() const override;
                void set_text( const std::string &text );
                void handle_event( const sf::Event &event ) override;
            private:
                sf::Text _text; /** The text meant to be displayed */
                void draw( sf::RenderTarget &target, sf::RenderStates states ) const override;
            };
        }
    }
}

#endif //SOKOBAN_LABEL_HPP
