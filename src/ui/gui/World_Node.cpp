#include "World_Node.hpp"

#include <utility>
#include <iostream>

using namespace sokoban::ui::gui;

World_Node::World_Node( sf::RenderWindow &window )
        : window( window )
          , world_view( window.getDefaultView() )
          , scene_graph()
          , scene_layers()
          , world_bounds( 0.f, 0.f, world_view.getSize().x, world_view.getSize().y )
{
    board = new model::Board();
    load_textures();
    build_scene();
}

World_Node::World_Node( sf::RenderWindow &window, std::string level )
        : window( window )
          , world_view( window.getDefaultView() )
          , scene_graph()
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
    /*for ( SceneNode *node: *scene_layers )
    {
        delete node;
    }*/
    delete scene_layers;
}

void World_Node::update( sf::Time dt )
{

}

void World_Node::draw()
{
    window.setView( world_view );
    window.draw( scene_graph );
}

void World_Node::load_textures()
{

}

void World_Node::build_scene()
{
    scene_layers = new std::vector< SceneNode * >();
    for ( int i = 0; i < board->get_world()->size() + 1; ++i )
    {
        SceneNode::Ptr layer( new SceneNode() );
        scene_layers->push_back( layer.get() );
        scene_graph.attach_child( std::move( layer ) );
    }

    int layers = 0;
    sf::Texture backgroundTexture = sf::Texture();
    sf::IntRect textureRect( world_bounds );
    backgroundTexture.loadFromFile( "assets/images/PNG/Ground_Concrete.png" );
    backgroundTexture.setRepeated( true );

    std::unique_ptr< SpriteNode > backgroundSprite( new SpriteNode( backgroundTexture, textureRect ) );
    backgroundSprite->setPosition( world_bounds.left, world_bounds.top );
    scene_layers->at( layers )->attach_child( std::move( backgroundSprite ) );

    layers++;

    for ( model::Actor *actor: *board->get_world() )
    {
        sf::Texture sprite_texture = sf::Texture();
        sprite_texture.loadFromFile( actor->get_asset() );
        std::unique_ptr< SpriteNode > actor_sprite( new SpriteNode( sprite_texture ) );
        actor_sprite->setPosition( actor->get_x(), actor->get_y() );
        scene_layers->at( layers )->attach_child( std::move( actor_sprite ) );
        layers++;
    }
}
