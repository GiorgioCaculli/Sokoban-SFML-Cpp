#include "State_Game.hpp"

#include "../../util/Logger.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

#include <cmath>
#include <ctime>
#include <random>
#include <utility>
#include <sstream>
#include <iostream>

using namespace sokoban::ui::gui;
using namespace sokoban::util;
float base_volume = 10.f;
float unfocused_volume = base_volume / 3.f;
std::vector< std::string > _levels;
int current_level;
int steps_counter;
int reset_counter;

State_Game::State_Game( sf::RenderWindow &window, const std::vector< std::string > &levels, int start_level )
        : _window( window )
          , _world_view( window.getDefaultView() )
          , _scene_layers()
          , _world_bounds( 0.f, 0.f, _world_view.getSize().x, _world_view.getSize().y )
          , _player_is_moving_up( false )
          , _player_is_moving_down( false )
          , _player_is_moving_left( false )
          , _player_is_moving_right( false )
          , _board_player( nullptr )
          , _level( levels.at( start_level ) )
          , _board( _level )
          , _player_sprite( nullptr )
          , _box_texture_sheet( nullptr )
          , _platform_texture_sheet( nullptr )
          , _wall_texture_sheet( nullptr )
          , _player_texture_sheet( nullptr )
          , _background_texture( nullptr )
          , _font( nullptr )
          , _text( nullptr )
{
    _font = new sf::Font();
    _font->loadFromFile( "assets/fonts/ConnectionIi-2wj8.otf" );
    _text = new sf::Text();
    _text->setFillColor( sf::Color::Black );
    _levels = levels;
    current_level = start_level;
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
    std::cout << _board << std::endl;
    build_scene( levels.at( current_level ) );
}

State_Game::~State_Game()
{
    delete _font;
    delete _text;
    for ( sf::Sprite *layer: _scene_layers )
    {
        delete layer;
    }
    _scene_layers.clear();
    delete _box_texture_sheet;
    delete _platform_texture_sheet;
    delete _wall_texture_sheet;
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
    if ( _player_is_moving_up )
    {
        auto player_asset_rect = _board_player->get_player_face_map().find( model::Player::Face::NORTH )->second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->setTexture( *_player_texture_sheet );
        _player_sprite->setTextureRect( player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.TOP_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.TOP_COLLISION ) )
        {
            return;
        }
        else
        {
            for ( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
            }
        }
        _player_sprite->move( 0.f, -SPACE );
        _board_player->set_y( _board_player->get_y() - SPACE );
    }
    if ( _player_is_moving_down )
    {
        auto player_asset_rect = _board_player->get_player_face_map().find( model::Player::Face::SOUTH )->second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->setTexture( *_player_texture_sheet );
        _player_sprite->setTextureRect( player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.BOTTOM_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.BOTTOM_COLLISION ) )
        {
            return;
        }
        else
        {
            for ( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
            }
        }
        _player_sprite->move( 0.f, +SPACE );
        _board_player->set_y( _board_player->get_y() + SPACE );
    }
    if ( _player_is_moving_left )
    {
        auto player_asset_rect = _board_player->get_player_face_map().find( model::Player::Face::WEST )->second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->setTexture( *_player_texture_sheet );
        _player_sprite->setTextureRect( player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.LEFT_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.LEFT_COLLISION ) )
        {
            return;
        }
        else
        {
            for ( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
            }
        }
        _player_sprite->move( -SPACE, 0.f );
        _board_player->set_x( _board_player->get_x() - SPACE );
    }
    if ( _player_is_moving_right )
    {
        auto player_asset_rect = _board_player->get_player_face_map().find( model::Player::Face::EAST )->second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords, player_height_coords );
        _player_sprite->setTexture( *_player_texture_sheet );
        _player_sprite->setTextureRect( player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.RIGHT_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.RIGHT_COLLISION ) )
        {
            return;
        }
        else
        {
            for ( int i = 0; i < _box_actors.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x(), _box_actors.at( i )->get_y() );
            }
        }
        _player_sprite->move( +SPACE, 0.f );
        _board_player->set_x( _board_player->get_x() + SPACE );
    }
    _text->setString( "Steps: " + std::to_string( steps_counter ) + "\n" +
            "Resets: " + std::to_string( reset_counter ) );
    if ( _board.is_completed() )
    {
        /* TODO: BLINKING TEXT WHEN FINISHED */
    }
}

void State_Game::draw()
{
    _window.setView( _world_view );
    for ( sf::Sprite *layer: _scene_layers )
    {
        _window.draw( *layer );
    }
    _window.draw( *_text );
}

void State_Game::load_textures()
{
    Logger::log( LoggerLevel::INFO, "Loading Textures..." );
    _player_texture_sheet = new sf::Texture();
    _player_texture_sheet->loadFromFile( "assets/images/Spritesheet/character_spritesheet.png" );
    _box_texture_sheet = new sf::Texture();
    _box_texture_sheet->loadFromFile( "assets/images/Spritesheet/boxes_spritesheet.png" );
    _platform_texture_sheet = new sf::Texture();
    _platform_texture_sheet->loadFromFile( "assets/images/Spritesheet/platforms_spritesheet.png" );
    _wall_texture_sheet = new sf::Texture();
    _wall_texture_sheet->loadFromFile( "assets/images/Spritesheet/wall_round_spritesheet.png" );
    _background_texture = new sf::Texture();
    _background_texture->loadFromFile( "assets/images/PNG/GroundGravel_Sand.png" );
}

void State_Game::build_scene( const std::string &level )
{
    Logger::log( LoggerLevel::INFO, "World Node init" );
    _player_is_moving_up = false;
    _player_is_moving_down = false;
    _player_is_moving_left = false;
    _player_is_moving_right = false;
    _text->setFont( *_font );
    _text->setPosition( 20.f, 20.f );
    _text->setCharacterSize( 20 );

    Logger::log( LoggerLevel::INFO, "Board size: " + std::to_string( _board.get_world().size() ) );
    _box_sprites = std::vector< sf::Sprite * >();
    _box_actors = std::vector< model::Box * >();

    Logger::log( LoggerLevel::INFO, "Building Scene..." );
    std::size_t world_size = _board.get_world().size() + 1;
    _scene_layers = std::vector< sf::Sprite * >();
    std::stringstream ss;
    ss << "Initializing " << std::to_string( world_size ) << " Scene nodes...";
    Logger::log( LoggerLevel::DEBUG, ss.str() );


    std::random_device rd;
    std::mt19937 mt( rd() );

    int min_within_enum;
    int max_within_enum;

    min_within_enum = static_cast< int >( model::Box::Color::BEIGE_LIGHT );
    max_within_enum = static_cast< int >( model::Box::Color::YELLOW_LIGHT );
    std::uniform_int_distribution< int > box_distribution( min_within_enum, max_within_enum );
    auto random_box_color = static_cast< model::Box::Color >( box_distribution( mt ) );

    min_within_enum = static_cast< int >( model::Platform::Color::BEIGE );
    max_within_enum = static_cast< int >( model::Platform::Color::YELLOW );
    std::uniform_int_distribution< int > platform_distribution( min_within_enum, max_within_enum );
    auto random_platform_color = static_cast< model::Platform::Color >( platform_distribution( mt ) );

    min_within_enum = static_cast< int >( model::Wall::Color::BEIGE );
    max_within_enum = static_cast< int >( model::Wall::Color::BROWN );
    std::uniform_int_distribution< int > wall_distribution( min_within_enum, max_within_enum );
    auto random_wall_color = static_cast< model::Wall::Color >( wall_distribution( mt ) );

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

        sf::IntRect asset_rect;

        sf::Sprite *actor_sprite = nullptr;

        if ( actor->get_type() == actor->PLAYER )
        {
            _board_player = dynamic_cast< model::Player * >( actor );
            auto player_asset_rect = _board_player->get_player_face_map().find( model::Player::Face::SOUTH )->second;
            asset_coord_x = player_asset_rect.at( 0 );
            asset_coord_y = player_asset_rect.at( 1 );
            asset_coord_width = player_asset_rect.at( 2 );
            asset_coord_height = player_asset_rect.at( 3 );
            asset_rect = sf::IntRect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new sf::Sprite( *_player_texture_sheet, asset_rect );
            _player_sprite = actor_sprite;
        }
        if ( actor->get_type() == actor->PLATFORM )
        {
            auto *platform_actor = dynamic_cast< model::Platform * >( actor );
            auto platform_asset_rect = platform_actor->get_platform_color_map().find( random_platform_color )->second;
            asset_coord_x = platform_asset_rect.at( 0 );
            asset_coord_y = platform_asset_rect.at( 1 );
            asset_coord_width = platform_asset_rect.at( 2 );
            asset_coord_height = platform_asset_rect.at( 3 );
            asset_rect = sf::IntRect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new sf::Sprite( *_platform_texture_sheet, asset_rect );
            /* If sprite size = 32x32 */
            actor_sprite->setOrigin(
                    -( asset_coord_width / 2.f ),
                    -( asset_coord_height / 2.f )
            );
        }
        if ( actor->get_type() == actor->BOX )
        {
            auto *box_actor = dynamic_cast< model::Box * >( actor );
            auto box_asset_rect = box_actor->get_box_color_map().find( random_box_color )->second;
            asset_coord_x = box_asset_rect.at( 0 );
            asset_coord_y = box_asset_rect.at( 1 );
            asset_coord_width = box_asset_rect.at( 2 );
            asset_coord_height = box_asset_rect.at( 3 );
            sf::IntRect asset_rect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new sf::Sprite( *_box_texture_sheet, asset_rect );
            _box_sprites.push_back( actor_sprite );
            _box_actors.push_back( box_actor );
        }
        if ( actor->get_type() == actor->WALL )
        {
            auto *wall_actor = dynamic_cast< model::Wall * >( actor );
            auto wall_asset_rect = wall_actor->get_wall_color_map().find( random_wall_color )->second;
            asset_coord_x = wall_asset_rect.at( 0 );
            asset_coord_y = wall_asset_rect.at( 1 );
            asset_coord_width = wall_asset_rect.at( 2 );
            asset_coord_height = wall_asset_rect.at( 3 );
            asset_rect = sf::IntRect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new sf::Sprite( *_wall_texture_sheet, asset_rect );
        }
        actor_sprite->setPosition( actor->get_x(), actor->get_y() );
        _scene_layers.push_back( actor_sprite );
        layers++;
    }

    Logger::log( LoggerLevel::INFO, "Number of layers loaded: " + std::to_string( layers ) );
}

void State_Game::handle_player_input( sf::Keyboard::Key key, bool is_pressed )
{
    if ( _board.is_completed() )
    {
        _text->setCharacterSize( 50 );
        _text->setPosition( _world_view.getSize().x / 3.0f, _world_view.getSize().y / 2.f );
        _text->setString( "Level Completed\nPress ENTER to continue!" );
        if ( key == sf::Keyboard::Enter )
        {
            current_level += 1;
            if ( _levels.size() == current_level )
            {
                _text->setCharacterSize( 50 );
                _text->setPosition( _world_view.getSize().x / 3.0f, _world_view.getSize().y / 2.f );
                _text->setString( "All Levels Completed!" );
                return;
            }
            _level = _levels.at( current_level );
            reset_counter = 0;
            reset_board();
        }
    }
    else
    {
        if ( is_pressed )
        {
            step_sound.play();
            steps_counter++;
            if ( key == sf::Keyboard::R )
            {
                reset_board();
                reset_counter++;
            }
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

void State_Game::reset_board()
{
    steps_counter = 0;
    _window.clear();
    for ( sf::Sprite *layer: _scene_layers )
    {
        delete layer;
    }
    _scene_layers.clear();
    for ( model::Actor *actor: _board.get_world() )
    {
        delete actor;
    }
    _box_sprites.clear();
    _box_actors.clear();
    _board = model::Board( _level );
    build_scene( _level );
}
