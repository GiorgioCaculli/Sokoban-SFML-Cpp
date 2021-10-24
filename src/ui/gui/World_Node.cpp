#include "World_Node.hpp"

#include <utility>
#include <sstream>
#include <iostream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

sf::Texture *base_sokoban_texture;
sf::Texture *backgroundTexture;

sf::Music music;
sf::SoundBuffer step_buffer;
sf::Sound step_sound;
sf::SoundBuffer box_move_buffer;
sf::Sound box_move_sound;
float base_volume = 10.f;
float unfocused_volume = base_volume / 3.f;

World_Node::World_Node( sf::RenderWindow &window, std::string level )
        : _window( window )
          , _world_view( window.getDefaultView() )
          , _scene_layers()
          , _world_bounds( 0.f, 0.f, _world_view.getSize().x, _world_view.getSize().y )
          , _player_is_moving_up( false )
          , _player_is_moving_down( false )
          , _player_is_moving_left( false )
          , _player_is_moving_right( false )
          , _board_player( nullptr )
          , _level( level )
          , _board( _level )
{
    music.openFromFile( "assets/music/Town_-_Tavern_Tune.ogg" );
    music.play();
    music.setVolume( base_volume );
    music.setLoop( true );
    step_buffer.loadFromFile( "assets/sounds/footsteps_outdoor_boots.ogg" );
    step_sound.setBuffer( step_buffer );
    step_sound.setVolume( base_volume );
    box_move_buffer.loadFromFile( "assets/sounds/wood_creak_01.ogg" );
    box_move_sound.setBuffer( box_move_buffer );
    box_move_sound.setVolume( base_volume );
    load_textures();
    build_scene( level );
}

World_Node::~World_Node()
{
    delete _scene_layers;
    delete _scene_graph;
    delete base_sokoban_texture;
    delete backgroundTexture;
    delete _box_sprites;
    delete _box_actors;
}

void World_Node::update( const sf::Time &dt )
{
    float SPACE = 64.f;
    sf::IntRect player_assets_coords;
    int player_x_coords;
    int player_y_coords;
    int player_width_coords;
    int player_height_coords;
    if( _player_is_moving_up )
    {
        _board_player->set_face( model::Player::NORTH );
        player_x_coords = _board_player->get_asset_coords()[ 0 ];
        player_y_coords = _board_player->get_asset_coords()[ 1 ];
        player_width_coords = _board_player->get_asset_coords()[ 2 ];
        player_height_coords = _board_player->get_asset_coords()[ 3 ];
        player_assets_coords = sf::IntRect ( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->update_texture( *base_sokoban_texture, player_assets_coords );
        if( _board.check_wall_collision( _board_player, _board.TOP_COLLISION ) )
        {
            return;
        }
        if( _board.check_box_collision( _board.TOP_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < _box_actors->size(); i++ )
            {
                _box_sprites->at( i )->setPosition( _box_actors->at( i )->get_x(), _box_actors->at( i )->get_y() );
            }
        }
        _player_sprite->move( 0.f, -SPACE );
        _board_player->set_y( _board_player->get_y() - SPACE );
    }
    if( _player_is_moving_down )
    {
        _board_player->set_face( model::Player::SOUTH );
        player_x_coords = _board_player->get_asset_coords()[ 0 ];
        player_y_coords = _board_player->get_asset_coords()[ 1 ];
        player_width_coords = _board_player->get_asset_coords()[ 2 ];
        player_height_coords = _board_player->get_asset_coords()[ 3 ];
        player_assets_coords = sf::IntRect ( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->update_texture( *base_sokoban_texture, player_assets_coords );
        if( _board.check_wall_collision( _board_player, _board.BOTTOM_COLLISION ) )
        {
            return;
        }
        if( _board.check_box_collision( _board.BOTTOM_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < _box_actors->size(); i++ )
            {
                _box_sprites->at( i )->setPosition( _box_actors->at( i )->get_x(), _box_actors->at( i )->get_y() );
            }
        }
        _player_sprite->move( 0.f, +SPACE );
        _board_player->set_y( _board_player->get_y() + SPACE );
    }
    if( _player_is_moving_left )
    {
        _board_player->set_face( model::Player::EAST );
        player_x_coords = _board_player->get_asset_coords()[ 0 ];
        player_y_coords = _board_player->get_asset_coords()[ 1 ];
        player_width_coords = _board_player->get_asset_coords()[ 2 ];
        player_height_coords = _board_player->get_asset_coords()[ 3 ];
        player_assets_coords = sf::IntRect ( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->update_texture( *base_sokoban_texture, player_assets_coords );
        if( _board.check_wall_collision( _board_player, _board.LEFT_COLLISION ) )
        {
            return;
        }
        if( _board.check_box_collision( _board.LEFT_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < _box_actors->size(); i++ )
            {
                _box_sprites->at( i )->setPosition( _box_actors->at( i )->get_x(), _box_actors->at( i )->get_y() );
            }
        }
        _player_sprite->move( -SPACE, 0.f );
        _board_player->set_x( _board_player->get_x() - SPACE );
    }
    if( _player_is_moving_right )
    {
        _board_player->set_face( model::Player::WEST );
        player_x_coords = _board_player->get_asset_coords()[ 0 ];
        player_y_coords = _board_player->get_asset_coords()[ 1 ];
        player_width_coords = _board_player->get_asset_coords()[ 2 ];
        player_height_coords = _board_player->get_asset_coords()[ 3 ];
        player_assets_coords = sf::IntRect ( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->update_texture( *base_sokoban_texture, player_assets_coords );
        if( _board.check_wall_collision( _board_player, _board.RIGHT_COLLISION ) )
        {
            return;
        }
        if( _board.check_box_collision( _board.RIGHT_COLLISION ) )
        {
            return;
        }
        else
        {
            for( int i = 0; i < _box_actors->size(); i++ )
            {
                _box_sprites->at( i )->setPosition( _box_actors->at( i )->get_x(), _box_actors->at( i )->get_y() );
            }
        }
        _player_sprite->move( +SPACE, 0.f );
        _board_player->set_x( _board_player->get_x() + SPACE );
    }
    _scene_graph->update( dt );
}

void World_Node::draw()
{
    _window.setView( _world_view );
    _window.draw( *_scene_graph );
}

void World_Node::load_textures()
{
    Logger::log( LoggerLevel::INFO, "Loading Textures..." );
    base_sokoban_texture = new sf::Texture();
    base_sokoban_texture->loadFromFile( "assets/images/Spritesheet/sprites.png" );
    backgroundTexture = new sf::Texture();
    backgroundTexture->loadFromFile( "assets/images/PNG/GroundGravel_Sand.png" );
}


void World_Node::build_scene( const std::string &level )
{
    Logger::log( LoggerLevel::INFO, "World Node init" );

    Logger::log( LoggerLevel::INFO, "Board size: " + std::to_string( _board.get_world().size() ) );
    _scene_graph = new SceneNode();
    _box_sprites = new std::vector< SpriteNode *>();
    _box_actors = new std::vector< model::Box * >();

    Logger::log( LoggerLevel::INFO, "Building Scene..." );
    std::size_t world_size = _board.get_world().size() + 1;
    _scene_layers = new std::vector< SceneNode * >();
    std::stringstream ss;
    ss << "Initializing " << std::to_string( world_size ) << " fictional Scene nodes...";
    Logger::log( LoggerLevel::DEBUG, ss.str() );
    for ( int i = 0; i < world_size; ++i )
    {
        ss.str( std::string() );
        ss << "Initializing fictional node #" << std::to_string( i ) << "...\n";
        Logger::log( LoggerLevel::DEBUG, ss.str() );
        SceneNode *layer = new SceneNode();
        _scene_layers->push_back( layer );
        _scene_graph->attach_child( layer );
    }

    int layers = 0;
    sf::IntRect textureRect( _world_bounds );
    backgroundTexture->setRepeated( true );

    SpriteNode *backgroundSprite = new SpriteNode( *backgroundTexture, textureRect );
    backgroundSprite->setPosition( _world_bounds.left, _world_bounds.top );
    _scene_layers->at( layers )->attach_child( backgroundSprite );

    layers++;

    for ( model::Actor *actor: _board.get_world() )
    {
        int asset_coord_x = actor->get_asset_coords().at( 0 );
        int asset_coord_y = actor->get_asset_coords().at( 1 );
        int asset_coord_width = actor->get_asset_coords().at( 2 );
        int asset_coord_height = actor->get_asset_coords().at( 3 );

        sf::IntRect asset_rect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );

        SpriteNode *actor_sprite = new SpriteNode( *base_sokoban_texture, asset_rect );
        actor_sprite->setPosition( actor->get_x(), actor->get_y() );
        if( actor->get_type() == actor->PLAYER )
        {
            _board_player = dynamic_cast< model::Player * >( actor );
            _player_sprite = actor_sprite;
            actor_sprite->setOrigin(
                    -( asset_coord_width / 4.f ),
                    0.f
                    );
        }
        if( actor->get_type() == actor->PLATFORM )
        {
            actor_sprite->setOrigin(
                    -( asset_coord_width / 2.f ),
                    -( asset_coord_height / 2.f )
                    );
        }
        if( actor->get_type() == actor->BOX )
        {
            _box_sprites->push_back( actor_sprite );
            _box_actors->push_back( dynamic_cast< model::Box * >( actor ) );
        }
        _scene_layers->at( layers )->attach_child( actor_sprite );
        layers++;
    }

    Logger::log( LoggerLevel::INFO, "Number of layers loaded: " + std::to_string( layers ) );
}

void World_Node::handle_player_input( sf::Keyboard::Key key, bool is_pressed )
{
    if( is_pressed )
    {
        step_sound.play();
    }
    else
    {
        step_sound.stop();
    }
    if ( key == sf::Keyboard::Up )
    {
        _player_is_moving_up = is_pressed;
    }
    else if ( key == sf::Keyboard::Down )
    {
        _player_is_moving_down = is_pressed;
    }
    else if ( key == sf::Keyboard::Left )
    {
        _player_is_moving_left = is_pressed;
    }
    else if ( key == sf::Keyboard::Right )
    {
        _player_is_moving_right = is_pressed;
    }
    else if ( key == sf::Keyboard::R )
    {
        _window.clear();
        delete _scene_layers;
        delete _scene_graph;
        delete _box_sprites;
        delete _box_actors;
        for( model::Actor *actor : _board.get_world() )
        {
            delete actor;
        }
        _board = model::Board( _level );
        build_scene( _level );
    }
}

void World_Node::process_events()
{
    sf::Event event {};
    while ( _window.pollEvent( event ) )
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
            _window.close();
            break;
        case sf::Event::Resized:
            break;
        case sf::Event::LostFocus:
            music.setVolume( unfocused_volume );
            break;
        case sf::Event::GainedFocus:
            music.setVolume( base_volume );
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
