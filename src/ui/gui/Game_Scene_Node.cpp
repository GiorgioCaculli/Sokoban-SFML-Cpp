#include "Game_Scene_Node.hpp"

#include <string>
#include <utility>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

GameSceneNode::GameSceneNode( sf::RenderWindow &window, std::string level )
{
    Logger::log( LoggerLevel::INFO, "Initializing world..." );
    world = new World_Node( window, std::move( level ) );
}

GameSceneNode::GameSceneNode( sf::RenderWindow &window )
{
    Logger::log( LoggerLevel::INFO, "Initializing world..." );
    world = new World_Node( window );
}

GameSceneNode::~GameSceneNode()
{
    Logger::log( LoggerLevel::INFO, "Deleting world..." );
    delete world;
}

void GameSceneNode::update( sf::Time dt )
{
    world->update( dt );
}

void GameSceneNode::draw()
{
    world->draw();
}

void GameSceneNode::process_events()
{
    world->process_events();
}
