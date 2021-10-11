#include "Scene_Node.hpp"

#include <algorithm>
#include <cassert>
#include <sstream>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

SceneNode::SceneNode()
        : parent( nullptr )
{
    std::stringstream ss;
    ss << "SceneNode init";
    ss << " X: " << this->getPosition().x;
    ss << " Y: " << this->getPosition().y;
    Logger::log( LoggerLevel::INFO, ss.str() );
    children = new std::vector< SceneNode * >();
}

SceneNode::~SceneNode()
{
    for ( SceneNode *node: *children )
    {
        std::stringstream ss;
        ss << "Deletion child node: ";
        ss << "x: " << node->getPosition().x << " y: " << node->getPosition().y;
        ss << "\n";
        Logger::log( LoggerLevel::DEBUG, ss.str() );
        delete node;
    }
    Logger::log( LoggerLevel::DEBUG, "Scene nodes vector deletion." );
    delete children;
}

void SceneNode::attach_child( SceneNode *child )
{
    child->parent = this;
    children->push_back( child );
}

SceneNode *SceneNode::detach_child( const SceneNode *node )
{
    auto n = [ &node ]( SceneNode *p )
    { return p == node; };
    auto found = std::find_if( children->begin(), children->end(), n );
    assert( found != children->end() );
    SceneNode *result = *found;
    result->parent = nullptr;
    children->erase( found );
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
}

void SceneNode::update_children( sf::Time dt )
{
    for ( SceneNode *child: *children )
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
}

void SceneNode::draw_children( sf::RenderTarget &target, sf::RenderStates &states ) const
{
    for ( const SceneNode *child: *children )
    {
        child->draw( target, states );
    }
}
