#ifndef SOKOBAN_CONTAINER_HPP
#define SOKOBAN_CONTAINER_HPP

#include "Component.hpp"

#include <memory>
#include <vector>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Container
                    : public Component
            {
            public:
                typedef std::shared_ptr< Container > Ptr;
                Container();
                void pack( Component::Ptr component );
                bool is_selectable() const override;
                void handle_event( const sf::Event &event ) override;
            private:
                std::vector< Component::Ptr > _children;
                int _selected_child;
                void draw( sf::RenderTarget &target, sf::RenderStates states ) const override;
                bool has_selection() const;
                void select( std::size_t index );
                void select_next();
                void select_previous();
            };
        }
    }
}

#endif //SOKOBAN_CONTAINER_HPP
