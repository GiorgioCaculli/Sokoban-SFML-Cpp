#include "Game_State.hpp"

#include <string>
#include <utility>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

GameSceneNode::GameSceneNode( sf::RenderWindow &window, std::string level )
{
    Logger::log( LoggerLevel::INFO, "Initializing _world..." );
    _world = new World_Node( window, std::move( level ) );
}

GameSceneNode::GameSceneNode( sf::RenderWindow &window )
{
    Logger::log( LoggerLevel::INFO, "Initializing _world..." );
    _world = new World_Node( window, "assets/levels/tutorial.lvl" );
}

GameSceneNode::~GameSceneNode()
{
    Logger::log( LoggerLevel::INFO, "Deleting _world..." );
    delete _world;
}

void GameSceneNode::update( sf::Time dt )
{
    _world->update( dt );
}

void GameSceneNode::draw()
{
    _world->draw();
}

void GameSceneNode::process_events()
{
    _world->process_events();
}
