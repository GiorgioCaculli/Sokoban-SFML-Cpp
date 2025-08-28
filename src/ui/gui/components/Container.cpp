#include <ui/gui/components/Container.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

/**
 * Constructor for the container
 * No children by default and no selected child by default
 */
Container::Container()
    : _children()
      , _selected_child( -1 )
{
}

/**
 * Function meant to add a component to the children.
 * @param component The new child to add
 */
void Container::pack( Component::Ptr component )
{
    _children.push_back( component );
    if ( !has_selection() && component->is_selectable() )
    {
        select( _children.size() - 1 );
    }
}

/**
 * By default a container is not selectable
 */
bool Container::is_selectable() const
{
    return false;
}

/**
 * Function meant to interchange between the various children
 */
void Container::handle_event( const sf::Event& event )
{
    if ( has_selection() && _children[ _selected_child ]->is_active() )
    {
        _children[ _selected_child ]->handle_event( event );
    } else if ( event.type == sf::Event::KeyReleased )
    {
        if ( event.key.code == sf::Keyboard::Key::Up )
        {
            select_previous();
        } else if ( event.key.code == sf::Keyboard::Key::Down )
        {
            select_next();
        } else if ( event.key.code == sf::Keyboard::Key::Enter || event.key.code == sf::Keyboard::Key::Space )
        {
            if ( has_selection() )
            {
                _children[ _selected_child ]->activate();
            }
        }
    }
}

/**
 * Visually display each child of the container
 */
void Container::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    for ( const Component::Ptr& child: _children )
    {
        target.draw( *child, states );
    }
}

/**
 * Function meant to retrieve whether a container has a selected child
 */
bool Container::has_selection() const
{
    return _selected_child >= 0;
}

/**
 * Function meant to interchange between the different children
 * @param index The child that has been selected
 */
void Container::select( std::size_t index )
{
    if ( _children[ index ]->is_selectable() )
    {
        if ( has_selection() )
        {
            _children[ _selected_child ]->deselect();
        }
        _children[ index ]->select();
        _selected_child = index;
    }
}

/**
 * Function meant to select the following child within the list of children
 */
void Container::select_next()
{
    if ( !has_selection() )
    {
        return;
    }
    int next = _selected_child;
    do
    {
        next = ( next + 1 ) % _children.size();
    } while ( !_children[ next ]->is_selectable() );
    select( next );
}

/**
 * Function meant to select the previous child within the list of children
 */
void Container::select_previous()
{
    if ( !has_selection() )
    {
        return;
    }
    int prev = _selected_child;
    do
    {
        prev = ( prev + _children.size() - 1 ) % _children.size();
    } while ( !_children[ prev ]->is_selectable() );
    select( prev );
}
