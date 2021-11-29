#include "Scene_Node.hpp"

#include "Command.hpp"

#include <cassert>
#include <algorithm>

using namespace sokoban::ui::gui;

Scene_Node::Scene_Node()
        : _children()
          , _parent( nullptr )
{
}

void Scene_Node::attach_child( Scene_Node::Ptr child )
{
    child->_parent = this;
    _children.push_back( std::move( child ) );
}

Scene_Node::Ptr Scene_Node::detach_child( const Scene_Node &node )
{
    auto found = std::find_if( _children.begin(), _children.end(), [ & ]( Ptr &p )
    {
        return p.get() == &node;
    } );
    assert( found != _children.end() );

    Ptr result = std::move( *found );
    result->_parent = nullptr;
    _children.erase( found );
    return result;
}

void Scene_Node::update( sf::Time dt )
{
    update_current( dt );
    update_children( dt );
}

sf::Vector2f Scene_Node::get_world_positions() const
{
    return get_world_transform() * sf::Vector2f();
}

sf::Transform Scene_Node::get_world_transform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for ( const Scene_Node *node = this; node != nullptr; node = node->_parent )
    {
        transform = node->getTransform() * transform;
    }

    return transform;
}

void Scene_Node::on_command( const Command &command, sf::Time dt )
{
    if ( command._category & get_category() )
    {
        command.action( *this, dt );
    }

    for ( Ptr &child : _children )
    {
        child->on_command( command, dt );
    }
}

unsigned int Scene_Node::get_category() const
{
    return Category::Scene;
}

void Scene_Node::update_current( sf::Time dt )
{
}

void Scene_Node::update_children( sf::Time dt )
{
    for ( Ptr &child : _children )
    {
        child->update( dt );
    }
}

void Scene_Node::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    draw_current( target, states );
    draw_children( target, states );
}

void Scene_Node::draw_current( sf::RenderTarget &target, sf::RenderStates states ) const
{
}

void Scene_Node::draw_children( sf::RenderTarget &target, sf::RenderStates states ) const
{
    for ( const Ptr &child : _children )
    {
        child->draw( target, states );
    }
}
