#include "Game_Scene_Node.hpp"

#include "../../model/Actor.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sokoban::ui::gui;

const int OFFSET = 64;
const int SPACE = 64;
std::vector< sf::Sprite * > *sprites;
std::vector< sf::Texture * > *textures;
sf::Sprite *background_sprite;

GameSceneNode::GameSceneNode( sf::RenderWindow &window, std::string level )
        : window( window )
          , world_bounds( 0.f, 0.f, world_view.getSize().x, world_view.getSize().y )
{
    board = new model::Board( std::move( level ) );
    load_textures();
    draw();
}

GameSceneNode::GameSceneNode( sf::RenderWindow &window )
        : window( window )
          , world_bounds( 0.f, 0.f, 1920, 1080 )
{
    board = new model::Board();
    load_textures();
    draw();
}

GameSceneNode::~GameSceneNode()
{
    delete board;
    for( sf::Sprite *sprite : *sprites )
    {
        delete sprite;
    }
    for( sf::Texture *texture : *textures )
    {
        delete texture;
    }
    delete sprites;
    delete textures;
    delete background_sprite;
}

void GameSceneNode::load_textures()
{
    sf::Texture backgroundTexture;
    sf::IntRect textureRect( world_bounds );
    backgroundTexture.loadFromFile( "assets/images/PNG/Ground_Concrete.png" );
    backgroundTexture.setRepeated( true );
    background_sprite = new sf::Sprite( backgroundTexture, textureRect );
    background_sprite->setPosition( world_bounds.left, world_bounds.top );

    sprites = new std::vector< sf::Sprite * >();
    textures = new std::vector< sf::Texture * >();
    for( model::Actor *actor : *board->get_world() )
    {
        sf::Sprite *actor_sprite = new sf::Sprite();
        sf::Texture *sprite_texture = new sf::Texture();
        sprite_texture->loadFromFile( actor->get_asset() );
        actor_sprite->setTexture( *sprite_texture );
        actor_sprite->setPosition( actor->get_x(), actor->get_y() );
        sprites->insert( sprites->begin(), actor_sprite );
        textures->insert( textures->begin(), sprite_texture );
    }
}

void GameSceneNode::build_scene()
{
}

void GameSceneNode::update( sf::Time dt )
{
}

void GameSceneNode::draw()
{
    window.draw( *background_sprite );
    for( sf::Sprite *sprite : *sprites )
    {
        window.draw( *sprite );
    }
}
