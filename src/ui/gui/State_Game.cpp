#include "State_Game.hpp"

#include <utility>
#include <sstream>
#include <iostream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;
float base_volume = 10.f;
float unfocused_volume = base_volume / 3.f;

State_Game::State_Game( sf::RenderWindow &window, const std::string& level )
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
          , _player_sprite( nullptr )
          , _base_sokoban_texture( nullptr )
          , _background_texture( nullptr )
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

State_Game::~State_Game()
{
    for( sf::Sprite *layer : _scene_layers )
    {
        delete layer;
    }
    _scene_layers.clear();
    delete _base_sokoban_texture;
    delete _background_texture;
    _box_sprites.clear();
    _box_actors.clear();
}

void State_Game::update( const sf::Time &dt )
{
    float SPACE = 64.f;
    sf::IntRect player_assets_coords;
    float player_x_coords;
    float player_y_coords;
    float player_width_coords;
    float player_height_coords;
    if( _player_is_moving_up )
    {
        _board_player->set_face( model::Player::NORTH );
        player_x_coords = _board_player->get_asset_coords()[ 0 ];
        player_y_coords = _board_player->get_asset_coords()[ 1 ];
        player_width_coords = _board_player->get_asset_coords()[ 2 ];
        player_height_coords = _board_player->get_asset_coords()[ 3 ];
        player_assets_coords = sf::IntRect ( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->setTexture( *_base_sokoban_texture );
        _player_sprite->setTextureRect( player_assets_coords );
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
            for( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
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
        _player_sprite->setTexture( *_base_sokoban_texture );
        _player_sprite->setTextureRect( player_assets_coords );
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
            for( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
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
        _player_sprite->setTexture( *_base_sokoban_texture );
        _player_sprite->setTextureRect( player_assets_coords );
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
            for( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
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
        _player_sprite->setTexture( *_base_sokoban_texture );
        _player_sprite->setTextureRect( player_assets_coords );
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
            for( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
            }
        }
        _player_sprite->move( +SPACE, 0.f );
        _board_player->set_x( _board_player->get_x() + SPACE );
    }
}

void State_Game::draw()
{
    _window.setView( _world_view );
    for( sf::Sprite *layer : _scene_layers )
    {
        _window.draw( *layer );
    }
}

void State_Game::load_textures()
{
    Logger::log( LoggerLevel::INFO, "Loading Textures..." );
    _base_sokoban_texture = new sf::Texture();
    _base_sokoban_texture->loadFromFile( "assets/images/Spritesheet/sprites.png" );
    _background_texture = new sf::Texture();
    _background_texture->loadFromFile( "assets/images/PNG/GroundGravel_Sand.png" );
}


void State_Game::build_scene( const std::string &level )
{
    Logger::log( LoggerLevel::INFO, "World Node init" );

    Logger::log( LoggerLevel::INFO, "Board size: " + std::to_string( _board.get_world().size() ) );
    _box_sprites = std::vector< sf::Sprite * >();
    _box_actors = std::vector< model::Box * >();

    Logger::log( LoggerLevel::INFO, "Building Scene..." );
    std::size_t world_size = _board.get_world().size() + 1;
    _scene_layers = std::vector< sf::Sprite * >();
    std::stringstream ss;
    ss << "Initializing " << std::to_string( world_size ) << " fictional Scene nodes...";
    Logger::log( LoggerLevel::DEBUG, ss.str() );

    int layers = 0;
    sf::IntRect textureRect( _world_bounds );
    _background_texture->setRepeated( true );

    auto *backgroundSprite = new sf::Sprite( *_background_texture, textureRect );
    backgroundSprite->setPosition( _world_bounds.left, _world_bounds.top );
    _scene_layers.push_back( backgroundSprite );

    layers++;

    for ( model::Actor *actor: _board.get_world() )
    {
        float asset_coord_x = actor->get_asset_coords().at( 0 );
        float asset_coord_y = actor->get_asset_coords().at( 1 );
        float asset_coord_width = actor->get_asset_coords().at( 2 );
        float asset_coord_height = actor->get_asset_coords().at( 3 );

        sf::IntRect asset_rect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );

        auto *actor_sprite = new sf::Sprite( *_base_sokoban_texture, asset_rect );
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
            _box_sprites.push_back( actor_sprite );
            _box_actors.push_back( dynamic_cast< model::Box * >( actor ) );
        }
        _scene_layers.push_back( actor_sprite );
        layers++;
    }

    Logger::log( LoggerLevel::INFO, "Number of layers loaded: " + std::to_string( layers ) );
}

void State_Game::handle_player_input( sf::Keyboard::Key key, bool is_pressed )
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
        for( sf::Sprite *layer : _scene_layers )
        {
            delete layer;
        }
        _scene_layers.clear();
        for( model::Actor *actor : _board.get_world() )
        {
            delete actor;
        }
        _box_sprites.clear();
        _box_actors.clear();
        _board = model::Board( _level );
        build_scene( _level );
    }
}

void State_Game::process_events()
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
