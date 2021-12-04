#include "Container.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sokoban::ui::gui;

Container::Container()
: _children()
, _selected_child( -1 )
{
}

void Container::pack( Component::Ptr component )
{
    _children.push_back( component );
    if( !has_selection() && component->is_selectable() )
    {
        select( _children.size() -1 );
    }
}

bool Container::is_selectable() const
{
    return false;
}

void Container::handle_event( const sf::Event &event )
{
    if( has_selection() && _children[ _selected_child ]->is_active() )
    {
        _children[ _selected_child ]->handle_event( event );
    }
    else if( event.type == sf::Event::KeyReleased )
    {
        if( event.key.code == sf::Keyboard:: Up )
        {
            select_previous();
        }
        else if( event.key.code == sf::Keyboard::Down )
        {
            select_next();
        }
        else if( event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space )
        {
            if( has_selection() )
            {
                _children[ _selected_child ]->activate();
            }
        }
    }
}

void Container::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    for( const Component::Ptr &child : _children )
    {
        target.draw( *child, states );
    }
}

bool Container::has_selection() const
{
    return _selected_child >= 0;
}

void Container::select( std::size_t index )
{
    if( _children[ index ]->is_selectable() )
    {
        if( has_selection() )
        {
            _children[ _selected_child ]->deselect();
        }
        _children[ index ]->select();
        _selected_child = index;
    }
}

void Container::select_next()
{
    if( !has_selection() )
    {
        return;
    }
    int next = _selected_child;
    do
    {
        next = ( next + 1 ) % _children.size();
    }
    while ( !_children[ next ]->is_selectable() );
    select( next );
}

void Container::select_previous()
{
    if( !has_selection() )
    {
        return;
    }
    int prev = _selected_child;
    do
    {
        prev = ( prev + _children.size() - 1 ) % _children.size();
    }
    while ( !_children[ prev ]->is_selectable() );
    select( prev );
}
