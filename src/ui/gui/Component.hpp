#ifndef SOKOBAN_COMPONENT_HPP
#define SOKOBAN_COMPONENT_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace sf
{
    class Event;
}

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Component
        : public sf::Drawable
        , public sf::Transformable
        , private sf::NonCopyable
            {
            public:
                typedef std::shared_ptr< Component > Ptr;
                Component();
                virtual ~Component();
                virtual bool is_selectable() const = 0;
                bool is_selected() const;
                virtual void select();
                virtual void deselect();
                virtual bool is_active() const;
                virtual void activate();
                virtual void deactivate();
                virtual void handle_event( const sf::Event &event ) = 0;
            private:
                bool _is_selected;
                bool _is_active;
            };
        }
    }
}

#endif //SOKOBAN_COMPONENT_HPP
