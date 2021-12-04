#ifndef SOKOBAN_LABEL_HPP
#define SOKOBAN_LABEL_HPP

#include "Component.hpp"
#include "Resource_Identifiers.hpp"
#include "../Resource_Holder.hpp"

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
                typedef std::shared_ptr< Label > Ptr;
                Label( const std::string &text, const Font_Holder &fonts );
                bool is_selectable() const override;
                void set_text( const std::string &text );
                void handle_event( const sf::Event &event ) override;
            private:
                sf::Text _text;
                void draw( sf::RenderTarget &target, sf::RenderStates states ) const;
            };
        }
    }
}

#endif //SOKOBAN_LABEL_HPP
