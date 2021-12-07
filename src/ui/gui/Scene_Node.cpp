#include "Scene_Node.hpp"

#include "Utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>
#include <cassert>
#include <algorithm>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the scene node
 * @param category The category that characterize the Scene node
 */
Scene_Node::Scene_Node( Category::Type category )
        : _children()
          , _parent( nullptr )
          , _default_category( category )
{
}

/**
 * Function to append a new node child within the Scene node
 * @param child The new child to append
 */
void Scene_Node::attach_child( Scene_Node::Ptr child )
{
    child->_parent = this;
    _children.push_back( std::move( child ) );
}

/**
 * The node that needs to be detached from the children
 * @param node The node to detach
 * @return The node that has been detached
 */
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

/**
 * Function that
 * @param dt
 * @param commands
 */
void Scene_Node::update( sf::Time dt, Command_Queue &commands )
{
    update_current( dt, commands );
    update_children( dt, commands );
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

unsigned int Scene_Node::get_category() const
{
    return _default_category;
}

void Scene_Node::update_current( sf::Time dt, Command_Queue &commands )
{
}

void Scene_Node::update_children( sf::Time dt, Command_Queue &commands )
{
    for ( Ptr &child : _children )
    {
        child->update( dt, commands );
    }
}

void Scene_Node::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    draw_current( target, states );
    draw_children( target, states );
    /* FOR DEBUG REASONS */
    draw_bounding_rect( target, states );
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

sf::FloatRect Scene_Node::get_bounding_rect() const
{
    return {};
}

bool Scene_Node::is_marked_for_removal() const
{
    return is_destroyed();
}

bool Scene_Node::is_destroyed() const
{
    return false;
}

void Scene_Node::draw_bounding_rect( sf::RenderTarget &target, sf::RenderStates states ) const
{
    sf::FloatRect rect = get_bounding_rect();
    sf::RectangleShape shape;
    shape.setPosition( sf::Vector2f( rect.left, rect.top ) );
    shape.setSize( sf::Vector2f( rect.width, rect.height ) );
    shape.setFillColor( sf::Color::Transparent );
    shape.setOutlineColor( sf::Color::Green );
    shape.setOutlineThickness( 1.f );
    target.draw( shape );
}
