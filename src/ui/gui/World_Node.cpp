#include "World_Node.hpp"

#include <utility>
#include <sstream>
#include <iostream>

#include <SFML/Graphics/Text.hpp>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

/*std::vector< sf::Sprite * > *sprites;*/

World_Node::World_Node( sf::RenderWindow &window )
        : window( window )
          , world_view( window.getDefaultView() )
          , scene_layers()
          , world_bounds( 0.f, 0.f, world_view.getSize().x, world_view.getSize().y )
{
    Logger::log( LoggerLevel::INFO, "World Node init" );
    Logger::log( LoggerLevel::INFO, "Loading board..." );
    board = new model::Board();
    Logger::log( LoggerLevel::INFO, "Board size: " + std::to_string( board->get_world()->size() ) );
    scene_graph = new SceneNode();
    /*sprites = new std::vector< sf::Sprite * >();*/
    load_textures();
    build_scene();
}

World_Node::World_Node( sf::RenderWindow &window, std::string level )
        : window( window )
          , world_view( window.getDefaultView() )
          , scene_layers()
          , world_bounds( 0.f, 0.f, world_view.getSize().x, world_view.getSize().y )
{
    board = new model::Board( std::move( level ) );
    load_textures();
    build_scene();
}

World_Node::~World_Node()
{
    delete board;
    delete scene_layers;
    delete scene_graph;
    /*for( sf::Sprite *sprite : *sprites )
    {
        delete sprite;
    }
    delete sprites;*/
}

void World_Node::update( sf::Time dt )
{

}

void World_Node::draw()
{
    window.setView( world_view );
    window.draw( *scene_graph );
}

void World_Node::load_textures()
{
    Logger::log( LoggerLevel::INFO, "Loading Textures..." );
}


void World_Node::build_scene()
{
    Logger::log( LoggerLevel::INFO, "Building Scene..." );
    std::size_t world_size = board->get_world()->size() + 1;
    scene_layers = new std::vector< SceneNode * >();
    std::stringstream ss;
    ss << "Initializing " << std::to_string( world_size ) << " fictional Scene nodes...";
    Logger::log( LoggerLevel::DEBUG, ss.str() );
    for ( int i = 0; i < world_size; ++i )
    {
        ss.str( std::string() );
        ss << "Initializing fictional node #" << std::to_string( i ) << "...\n";
        Logger::log( LoggerLevel::DEBUG, ss.str() );
        SceneNode *layer = new SceneNode();
        scene_layers->push_back( layer );
        scene_graph->attach_child( layer );
    }

    int layers = 0;
    sf::Texture *backgroundTexture = new sf::Texture();
    sf::IntRect textureRect( world_bounds );
    backgroundTexture->loadFromFile( "assets/images/PNG/GroundGravel_Sand.png" );
    backgroundTexture->setRepeated( true );

    SpriteNode *backgroundSprite = new SpriteNode( *backgroundTexture, textureRect );
    backgroundSprite->setPosition( world_bounds.left, world_bounds.top );
    scene_layers->at( layers )->attach_child( backgroundSprite );

    layers++;

    for ( const model::Actor *actor: *board->get_world() )
    {
        sf::Texture *sprite_texture = new sf::Texture();
        sprite_texture->loadFromFile( actor->get_asset() );
        SpriteNode *actor_sprite = new SpriteNode( *sprite_texture );
        actor_sprite->setPosition( actor->get_x(), actor->get_y() );
        scene_layers->at( layers )->attach_child( actor_sprite );
        layers++;
    }

    Logger::log( LoggerLevel::INFO, "Number of layers loaded: " + std::to_string( layers ) );
}
