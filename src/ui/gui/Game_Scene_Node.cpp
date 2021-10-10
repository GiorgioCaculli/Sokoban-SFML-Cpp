#include "Game_Scene_Node.hpp"

#include <string>
#include <utility>

using namespace sokoban::ui::gui;

GameSceneNode::GameSceneNode( sf::RenderWindow &window, std::string level )
        : window( window )
          , world( window, std::move( level ) )
{
}

GameSceneNode::GameSceneNode( sf::RenderWindow &window )
        : window( window )
          , world( window )
{
}

GameSceneNode::~GameSceneNode()
= default;

void GameSceneNode::update( sf::Time dt )
{
    world.update( dt );
}

void GameSceneNode::draw()
{
    world.draw();
}
