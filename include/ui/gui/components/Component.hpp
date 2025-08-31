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


namespace sokoban::ui::gui
{
    class Component
            : public sf::Drawable
              , public sf::Transformable
              , sf::NonCopyable
    {
    public:
        /** Generic declaration of a shared pointer meant to define a base nature to said pointer */
        typedef std::shared_ptr< Component > Ptr;

        Component();

        ~Component() override;

        virtual bool is_selectable() const = 0;

        bool is_selected() const;

        virtual void select();

        virtual void deselect();

        virtual bool is_active() const;

        virtual void activate();

        virtual void deactivate();

        virtual void handle_event( const sf::Event& event ) = 0;

    private:
        bool _is_selected; /** Check whether the component is selected */
        bool _is_active; /** Check whether the component is active */
    };
}


#endif //SOKOBAN_COMPONENT_HPP
