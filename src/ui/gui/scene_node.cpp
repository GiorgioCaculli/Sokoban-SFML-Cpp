#include "scene_node.hpp"

#include <algorithm>
#include <cassert>

using namespace sokoban::ui::gui;

SceneNode::SceneNode()
        : children()
          , parent( nullptr )
{

}

void SceneNode::attach_child( SceneNode::Ptr child )
{
    child->parent = this;
    children.push_back( std::move( child ) );
}

SceneNode::Ptr SceneNode::detach_child( const SceneNode &node )
{
    auto found = std::find_if( children.begin(), children.end(), [ & ]( Ptr &p )
    { return p.get() == &node; } );
    assert( found != children.end() );

    Ptr result = std::move( *found );
    result->parent = nullptr;
    children.erase( found );
    return result;
}

void SceneNode::update( sf::Time dt )
{
    update_current( dt );
    update_children( dt );
}

sf::Vector2f SceneNode::get_world_position() const
{
    return get_world_transform() * sf::Vector2f();
}

sf::Transform SceneNode::get_world_transform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for ( const SceneNode *node = this; node != nullptr; node = node->parent )
    {
        transform = node->getTransform() * transform;
    }
    return transform;
}

void SceneNode::update_current( sf::Time dt )
{
    /* Do nothing by default */
}

void SceneNode::update_children( sf::Time dt )
{
    for ( Ptr &child: children )
    {
        child->update( dt );
    }
}

void SceneNode::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    draw_current( target, states );
    draw_children( target, states );
}

void SceneNode::draw_current( sf::RenderTarget &target, sf::RenderStates states ) const
{
    /* Do nothing by default */
}

void SceneNode::draw_children( sf::RenderTarget &target, sf::RenderStates states ) const
{
    for ( const Ptr &child: children )
    {
        child->draw( target, states );
    }
}
