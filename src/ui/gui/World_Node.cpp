#include "World_Node.hpp"

#include <utility>
#include <sstream>
#include <iostream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

sf::Texture *player_texture_up;
sf::Texture *player_texture_down;
sf::Texture *player_texture_left;
sf::Texture *player_texture_right;

World_Node::World_Node( sf::RenderWindow &window )
        : window( window )
          , world_view( window.getDefaultView() )
          , scene_layers()
          , world_bounds( 0.f, 0.f, world_view.getSize().x, world_view.getSize().y )
{
    player_is_moving_up = false;
    player_is_moving_down = false;
    player_is_moving_left = false;
    player_is_moving_right = false;
    Logger::log( LoggerLevel::INFO, "World Node init" );
    Logger::log( LoggerLevel::INFO, "Loading board..." );
    board = new model::Board();
    Logger::log( LoggerLevel::INFO, "Board size: " + std::to_string( board->get_world()->size() ) );
    scene_graph = new SceneNode();
    box_sprites = new std::vector< SpriteNode *>();
    box_actors = new std::vector< model::Actor * >();
    player_texture_up = new sf::Texture();
    player_texture_up->loadFromFile( "assets/images/PNG/Character7.png" );
    player_texture_down = new sf::Texture();
    player_texture_down->loadFromFile( "assets/images/PNG/Character4.png" );
    player_texture_left = new sf::Texture();
    player_texture_left->loadFromFile( "assets/images/PNG/Character1.png" );
    player_texture_right = new sf::Texture();
    player_texture_right->loadFromFile( "assets/images/PNG/Character2.png" );
    load_textures();
    build_scene();
}

World_Node::World_Node( sf::RenderWindow &window, std::string level )
        : window( window )
          , world_view( window.getDefaultView() )
          , scene_layers()
          , world_bounds( 0.f, 0.f, world_view.getSize().x, world_view.getSize().y )
{
    player_is_moving_up = false;
    player_is_moving_down = false;
    player_is_moving_left = false;
    player_is_moving_right = false;
    Logger::log( LoggerLevel::INFO, "World Node init" );
    Logger::log( LoggerLevel::INFO, "Loading board..." );
    board = new model::Board( std::move( level ) );
    Logger::log( LoggerLevel::INFO, "Board size: " + std::to_string( board->get_world()->size() ) );
    scene_graph = new SceneNode();
    load_textures();
    build_scene();
}

World_Node::~World_Node()
{
    delete board;
    delete scene_layers;
    delete scene_graph;
    delete player_texture_up;
    delete player_texture_down;
    delete player_texture_left;
    delete player_texture_right;
}

void World_Node::update( sf::Time dt )
{
    float SPACE = 64.f;
    if( player_is_moving_up )
    {
        player_sprite->set_texture( player_texture_up );
        if( board->check_wall_collision( board_player, board->TOP_COLLISION ) )
        {
            return;
        }
        if( board->check_box_collision( board->TOP_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < box_actors->size(); i++ )
            {
                box_sprites->at( i )->setPosition( box_actors->at( i )->get_x(), box_actors->at( i )->get_y() );
            }
        }
        player_sprite->move( 0.f, -SPACE );
        board_player->set_y( board_player->get_y() - SPACE );
    }
    if( player_is_moving_down )
    {
        player_sprite->set_texture( player_texture_down );
        if( board->check_wall_collision( board_player, board->BOTTOM_COLLISION ) )
        {
            return;
        }
        if( board->check_box_collision( board->BOTTOM_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < box_actors->size(); i++ )
            {
                box_sprites->at( i )->setPosition( box_actors->at( i )->get_x(), box_actors->at( i )->get_y() );
            }
        }
        player_sprite->move( 0.f, +SPACE );
        board_player->set_y( board_player->get_y() + SPACE );
    }
    if( player_is_moving_left )
    {
        player_sprite->set_texture( player_texture_left );
        if( board->check_wall_collision( board_player, board->LEFT_COLLISION ) )
        {
            return;
        }
        if( board->check_box_collision( board->LEFT_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < box_actors->size(); i++ )
            {
                box_sprites->at( i )->setPosition( box_actors->at( i )->get_x(), box_actors->at( i )->get_y() );
            }
        }
        player_sprite->move( -SPACE, 0.f );
        board_player->set_x( board_player->get_x() - SPACE );
    }
    if( player_is_moving_right )
    {
        player_sprite->set_texture( player_texture_right );
        if( board->check_wall_collision( board_player, board->RIGHT_COLLISION ) )
        {
            return;
        }
        if( board->check_box_collision( board->RIGHT_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < box_actors->size(); i++ )
            {
                box_sprites->at( i )->setPosition( box_actors->at( i )->get_x(), box_actors->at( i )->get_y() );
            }
        }
        player_sprite->move( +SPACE, 0.f );
        board_player->set_x( board_player->get_x() + SPACE );
    }
    scene_graph->update( dt );
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

    SpriteNode *backgroundSprite = new SpriteNode( backgroundTexture, textureRect );
    backgroundSprite->setPosition( world_bounds.left, world_bounds.top );
    scene_layers->at( layers )->attach_child( backgroundSprite );

    layers++;

    for ( model::Actor *actor: *board->get_world() )
    {
        sf::Texture *sprite_texture = new sf::Texture();
        sprite_texture->loadFromFile( actor->get_asset() );
        SpriteNode *actor_sprite = new SpriteNode( sprite_texture );
        actor_sprite->setPosition( actor->get_x(), actor->get_y() );
        if( actor->get_type() == actor->PLAYER )
        {
            board_player = actor;
            player_sprite = actor_sprite;
            actor_sprite->setOrigin(
                    -( sprite_texture->getSize().x / 4.f ),
                    0.f
                    );
        }
        if( actor->get_type() == actor->PLATFORM )
        {
            actor_sprite->setOrigin(
                    -( sprite_texture->getSize().x / 2.f ),
                    -( sprite_texture->getSize().y / 2.f )
                    );
        }
        if( actor->get_type() == actor->BOX )
        {
            box_sprites->push_back( actor_sprite );
            box_actors->push_back( actor );
        }
        scene_layers->at( layers )->attach_child( actor_sprite );
        layers++;
    }

    Logger::log( LoggerLevel::INFO, "Number of layers loaded: " + std::to_string( layers ) );
}

void World_Node::handle_player_input( sf::Keyboard::Key key, bool is_pressed )
{
    if ( key == sf::Keyboard::Up )
    {
        player_is_moving_up = is_pressed;
    }
    else if ( key == sf::Keyboard::Down )
    {
        player_is_moving_down = is_pressed;
    }
    else if ( key == sf::Keyboard::Left )
    {
        player_is_moving_left = is_pressed;
    }
    else if ( key == sf::Keyboard::Right )
    {
        player_is_moving_right = is_pressed;
    }
}

void World_Node::process_events()
{
    sf::Event event {};
    while ( window.pollEvent( event ) )
    {
        switch ( event.type )
        {
        case sf::Event::KeyPressed:
            handle_player_input( event.key.code, true );
            break;
        case sf::Event::KeyReleased:
            handle_player_input( event.key.code, false );
            break;
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::Resized:
            break;
        case sf::Event::LostFocus:
            break;
        case sf::Event::GainedFocus:
            break;
        case sf::Event::TextEntered:
            break;
        case sf::Event::MouseWheelMoved:
            break;
        case sf::Event::MouseWheelScrolled:
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::MouseEntered:
            break;
        case sf::Event::MouseLeft:
            break;
        case sf::Event::JoystickButtonPressed:
            break;
        case sf::Event::JoystickButtonReleased:
            break;
        case sf::Event::JoystickMoved:
            break;
        case sf::Event::JoystickConnected:
            break;
        case sf::Event::JoystickDisconnected:
            break;
        case sf::Event::TouchBegan:
            break;
        case sf::Event::TouchMoved:
            break;
        case sf::Event::TouchEnded:
            break;
        case sf::Event::SensorChanged:
            break;
        case sf::Event::Count:
            break;
        }
    }
}
