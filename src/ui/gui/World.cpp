#include <ui/gui/World.hpp>

#include <gzc/util/logger/Logger.hpp>
#include <ui/gui/Sound_Node.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>
#include <ctime>
#include <random>
#include <utility>
#include <sstream>
#include <iostream>

using namespace sokoban::ui::gui;
using namespace gzc::util::logger;

namespace
{
    float OFFSET = 64.f;
    int steps_counter = 0;
    Logger logger( "World", "sokoban.log", true );
}

/**
 * Default constructor for the world
 * @param target The target to display the sprites onto
 * @param board The board containing the various actors and the level's skeleton
 * @param fonts The various fonts used
 * @param sounds The various sound effects
 */
World::World( sf::RenderTarget& target, const core::Board& board, Font_Holder& fonts, Sound_Player& sounds )
    : _target( target )
      , _world_view( target.getDefaultView() )
      , _textures()
      , _fonts( fonts )
      , _sounds( sounds )
      , _scene_graph()
      , _scene_layers()
      , _player_is_moving_up( false )
      , _player_is_moving_down( false )
      , _player_is_moving_left( false )
      , _player_is_moving_right( false )
      , _world_bounds( 0.f, 0.f, _world_view.getSize().x, _world_view.getSize().y )
      , _board( "" )
      , _player_sprite( nullptr )
      , _board_player( nullptr )
      , _player_entity( nullptr )
      , _box_texture_sheet( nullptr )
      , _platform_texture_sheet( nullptr )
      , _wall_texture_sheet( nullptr )
      , _player_texture_sheet( nullptr )
      , _background_texture( nullptr )
      , _text( nullptr )
      , _reset_counter( 0 )
{
    _board = board;
    logger.log( Logger::Level::DEBUG, "Level Layout:" );
    for ( core::Actor* actor: _board.get_world() )
    {
        logger.log( Logger::Level::DEBUG, actor->to_string() );
    }
    /*step_buffer.loadFromFile( "assets/sounds/footsteps_outdoor_boots.ogg" );
    step_sound.setBuffer( step_buffer );
    step_sound.setVolume( 10.f );
    box_move_buffer.loadFromFile( "assets/sounds/wood_creak_01.ogg" );
    box_move_sound.setBuffer( box_move_buffer );
    box_move_sound.setVolume( 10.f );*/
    load_textures();
    build_scene();
    steps_counter = 0;
}

/**
 * Default destructor for the World
 */
World::~World()
{
    delete _text;
    for ( Scene_Node* layer: _scene_layers )
    {
        delete layer;
    }
    for ( entity::Entity* entity: _entities )
    {
        delete entity;
    }
    _scene_layers.clear();
    _entities.clear();
    delete _player_texture_sheet;
    delete _box_texture_sheet;
    delete _platform_texture_sheet;
    delete _wall_texture_sheet;
    delete _background_texture;
    _box_sprites.clear();
    _box_entities.clear();
}

/**
 * Realtime updates the visually available entities
 * @param dt The clock time
 */
void World::update( sf::Time dt )
{
    ( void ) dt; /* TODO: USAGE */
    float SPACE = 1.f;
    sf::IntRect player_assets_coords;
    float player_x_coords;
    float player_y_coords;
    float player_width_coords;
    float player_height_coords;
    if ( _player_is_moving_up )
    {
        auto player_asset_rect = _player_entity->get_player_face_map().find( entity::Entity_Player::Face::NORTH )->
                second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords,
                                            player_height_coords );
        _player_sprite->set_texture( *_player_texture_sheet );
        _player_sprite->set_texture( *_player_texture_sheet, player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.TOP_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.TOP_COLLISION ) )
        {
            return;
        } else
        {
            for ( long unsigned int i = 0; i < _box_entities.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x() * OFFSET,
                                                   _box_actors.at( i )->get_y() * OFFSET );
            }
        }
        _player_sprite->move( 0.f, -SPACE * OFFSET );
        _player_entity->set_y( _player_entity->get_y() - SPACE );
        _board_player->set_y( _board_player->get_y() - SPACE );
    }
    if ( _player_is_moving_down )
    {
        auto player_asset_rect = _player_entity->get_player_face_map().find( entity::Entity_Player::Face::SOUTH )->
                second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords,
                                            player_height_coords );
        _player_sprite->set_texture( *_player_texture_sheet, player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.BOTTOM_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.BOTTOM_COLLISION ) )
        {
            return;
        } else
        {
            for ( long unsigned int i = 0; i < _box_entities.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x() * OFFSET,
                                                   _box_actors.at( i )->get_y() * OFFSET );
            }
        }
        _player_sprite->move( 0.f, +SPACE * OFFSET );
        _player_entity->set_y( _player_entity->get_y() + SPACE );
        _board_player->set_y( _board_player->get_y() + SPACE );
    }
    if ( _player_is_moving_left )
    {
        auto player_asset_rect = _player_entity->get_player_face_map().find( entity::Entity_Player::Face::WEST )->
                second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords,
                                            player_height_coords );
        _player_sprite->set_texture( *_player_texture_sheet, player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.LEFT_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.LEFT_COLLISION ) )
        {
            return;
        } else
        {
            for ( long unsigned int i = 0; i < _box_entities.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x() * OFFSET,
                                                   _box_actors.at( i )->get_y() * OFFSET );
            }
        }
        _player_sprite->move( -SPACE * OFFSET, 0.f );
        _player_entity->set_x( _player_entity->get_x() - SPACE );
        _board_player->set_x( _board_player->get_x() - SPACE );
    }
    if ( _player_is_moving_right )
    {
        auto player_asset_rect = _player_entity->get_player_face_map().find( entity::Entity_Player::Face::EAST )->
                second;
        player_x_coords = player_asset_rect.at( 0 );
        player_y_coords = player_asset_rect.at( 1 );
        player_width_coords = player_asset_rect.at( 2 );
        player_height_coords = player_asset_rect.at( 3 );
        player_assets_coords = sf::IntRect( player_x_coords, player_y_coords, player_width_coords,
                                            player_height_coords );
        _player_sprite->set_texture( *_player_texture_sheet, player_assets_coords );
        if ( _board.check_wall_collision( _board_player, _board.RIGHT_COLLISION ) )
        {
            return;
        }
        if ( _board.check_box_collision( _board.RIGHT_COLLISION ) )
        {
            return;
        } else
        {
            for ( long unsigned int i = 0; i < _box_entities.size(); i++ )
            {
                _box_sprites.at( i )->setPosition( _box_actors.at( i )->get_x() * OFFSET,
                                                   _box_actors.at( i )->get_y() * OFFSET );
            }
        }
        _player_sprite->move( +SPACE * OFFSET, 0.f );
        _board_player->set_x( _board_player->get_x() + SPACE );
    }
    _text->setString(
        "Steps:  " + std::to_string( steps_counter ) + "\n" +
        "Resets:  " + std::to_string( get_reset_counter() ) + "\n" +
        "Move Up: Arrow Up" + "\n" +
        "Move Down: Arrow Down" + "\n" +
        "Move Left: Arrow Left" + "\n" +
        "Move Right: Arrow Right" + "\n" +
        "Reset Board: R" + "\n" +
        "Skip Level: S" + "\n" +
        "Undo Skip: X" + "\n" +
        "Pause Game: Escape" + "\n"
    );
    if ( _board.is_completed() )
    {
        //step_sound.stop();
        /* TODO: BLINKING TEXT WHEN FINISHED */
    }
}

/**
 * Visually display the various scene nodes that make up the world
 */
void World::draw()
{
    _target.setView( _world_view );
    for ( Scene_Node* layer: _scene_layers )
    {
        _target.draw( *layer );
    }
    _target.draw( *_text );
}

/**
 * Load the various sprite sheets
 */
void World::load_textures()
{
    logger.log( Logger::Level::INFO, "Loading Textures..." );
    _player_texture_sheet = new sf::Texture();
    _player_texture_sheet->loadFromFile( "assets/images/Spritesheet/character_spritesheet.png" );
    _box_texture_sheet = new sf::Texture();
    _box_texture_sheet->loadFromFile( "assets/images/Spritesheet/boxes_spritesheet.png" );
    _platform_texture_sheet = new sf::Texture();
    _platform_texture_sheet->loadFromFile( "assets/images/Spritesheet/platforms_spritesheet.png" );
    _wall_texture_sheet = new sf::Texture();
    _wall_texture_sheet->loadFromFile( "assets/images/Spritesheet/wall_round_spritesheet.png" );
    _background_texture = new sf::Texture();
}

/**
 * Build the scene based on the board's skeleton
 */
void World::build_scene()
{
    logger.log( Logger::Level::INFO, "World Node init" );
    _player_is_moving_up = false;
    _player_is_moving_down = false;
    _player_is_moving_left = false;
    _player_is_moving_right = false;
    _text = new sf::Text();
    _text->setFont( _fonts.get( Fonts::Connection_II ) );
    _text->setPosition(
        _target.getSize().x - 350.f,
        20.f );
    _text->setCharacterSize( 24 );
    _text->setFillColor( sf::Color::Black );

    logger.log( Logger::Level::INFO, "Board size: " + std::to_string( _board.get_world().size() ) );
    _box_sprites = std::vector< Sprite_Node * >();
    _box_actors = std::vector< core::Box * >();
    _box_entities = std::vector< entity::Entity_Box * >();

    logger.log( Logger::Level::INFO, "Building Scene..." );
    std::size_t world_size = _board.get_world().size() + 1;
    _scene_layers = std::vector< Scene_Node * >();
    std::stringstream ss;
    ss << "Initializing " << std::to_string( world_size ) << " Scene nodes...";
    logger.log( Logger::Level::DEBUG, ss.str() );

    std::random_device rd;
    std::mt19937 mt( rd() );

    int min_within_enum;
    int max_within_enum;

    min_within_enum = static_cast< int >( Background_Color::CONCRETE );
    max_within_enum = static_cast< int >( Background_Color::SAND );
    std::uniform_int_distribution< int > background_distribution( min_within_enum, max_within_enum );
    auto random_background_color = static_cast< Background_Color >( background_distribution( mt ) );
    switch ( random_background_color )
    {
        case Background_Color::CONCRETE:
            _background_texture->loadFromFile( "assets/images/PNG/GroundGravel_Concrete.png" );
            break;
        case Background_Color::DIRT:
            _background_texture->loadFromFile( "assets/images/PNG/GroundGravel_Dirt.png" );
            break;
        case Background_Color::GRASS:
            _background_texture->loadFromFile( "assets/images/PNG/GroundGravel_Grass.png" );
            break;
        case Background_Color::SAND:
            _background_texture->loadFromFile( "assets/images/PNG/GroundGravel_Sand.png" );
            break;
    }

    min_within_enum = static_cast< int >( entity::Entity_Box::Color::BEIGE_LIGHT );
    max_within_enum = static_cast< int >( entity::Entity_Box::Color::YELLOW_LIGHT );
    std::uniform_int_distribution< int > box_distribution( min_within_enum, max_within_enum );
    auto random_box_color = static_cast< entity::Entity_Box::Color >( box_distribution( mt ) );

    min_within_enum = static_cast< int >( entity::Entity_Platform::Color::BEIGE );
    max_within_enum = static_cast< int >( entity::Entity_Platform::Color::YELLOW );
    std::uniform_int_distribution< int > platform_distribution( min_within_enum, max_within_enum );
    auto random_platform_color = static_cast< entity::Entity_Platform::Color >( platform_distribution( mt ) );

    min_within_enum = static_cast< int >( entity::Entity_Wall::Color::BEIGE );
    max_within_enum = static_cast< int >( entity::Entity_Wall::Color::BROWN );
    std::uniform_int_distribution< int > wall_distribution( min_within_enum, max_within_enum );
    auto random_wall_color = static_cast< entity::Entity_Wall::Color >( wall_distribution( mt ) );

    int layers = 0;
    sf::IntRect textureRect( _world_bounds );
    _background_texture->setRepeated( true );

    auto* backgroundSprite = new Sprite_Node( *_background_texture, textureRect );
    backgroundSprite->setPosition( _world_bounds.left, _world_bounds.top );
    _scene_layers.push_back( backgroundSprite );

    layers++;

    for ( core::Actor* actor: _board.get_world() )
    {
        float asset_coord_x;
        float asset_coord_y;
        float asset_coord_width;
        float asset_coord_height;

        sf::IntRect asset_rect;

        Sprite_Node* actor_sprite = nullptr;

        entity::Entity* entity_actor = nullptr;

        if ( actor->get_type() == actor->PLAYER )
        {
            _board_player = dynamic_cast< core::Player * >( actor );
            entity_actor = new entity::Entity_Player( actor->get_x(), actor->get_y() );
            _player_entity = dynamic_cast< entity::Entity_Player * >( entity_actor );
            auto player_asset_rect = _player_entity->get_player_face_map().find( entity::Entity_Player::Face::SOUTH )->
                    second;
            asset_coord_x = player_asset_rect.at( 0 );
            asset_coord_y = player_asset_rect.at( 1 );
            asset_coord_width = player_asset_rect.at( 2 );
            asset_coord_height = player_asset_rect.at( 3 );
            asset_rect = sf::IntRect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new Sprite_Node( *_player_texture_sheet, asset_rect );
            _player_sprite = actor_sprite;
        }
        if ( actor->get_type() == actor->PLATFORM )
        {
            entity_actor = new entity::Entity_Platform( actor->get_x(), actor->get_y() );
            actor = dynamic_cast< entity::Entity_Platform * >( entity_actor );
            auto* platform_actor = dynamic_cast< entity::Entity_Platform * >( actor );
            auto platform_asset_rect = platform_actor->get_platform_color_map().find( random_platform_color )->second;
            asset_coord_x = platform_asset_rect.at( 0 );
            asset_coord_y = platform_asset_rect.at( 1 );
            asset_coord_width = platform_asset_rect.at( 2 );
            asset_coord_height = platform_asset_rect.at( 3 );
            asset_rect = sf::IntRect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new Sprite_Node( *_platform_texture_sheet, asset_rect );
            /* If sprite size = 32x32 */
            actor_sprite->setOrigin(
                -( asset_coord_width / 2.f ),
                -( asset_coord_height / 2.f )
            );
        }
        if ( actor->get_type() == actor->BOX )
        {
            _box_actors.push_back( dynamic_cast< core::Box * >( actor ) );
            entity_actor = new entity::Entity_Box( actor->get_x(), actor->get_y() );
            actor = dynamic_cast< entity::Entity_Box * >( entity_actor );
            auto* box_entity = dynamic_cast< entity::Entity_Box * >( actor );
            auto box_asset_rect = box_entity->get_box_color_map().find( random_box_color )->second;
            asset_coord_x = box_asset_rect.at( 0 );
            asset_coord_y = box_asset_rect.at( 1 );
            asset_coord_width = box_asset_rect.at( 2 );
            asset_coord_height = box_asset_rect.at( 3 );
            sf::IntRect asset_rect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new Sprite_Node( *_box_texture_sheet, asset_rect );
            _box_sprites.push_back( actor_sprite );
            _box_entities.push_back( box_entity );
        }
        if ( actor->get_type() == actor->WALL )
        {
            entity_actor = new entity::Entity_Wall( actor->get_x(), actor->get_y() );
            actor = dynamic_cast< entity::Entity_Wall * >( entity_actor );
            auto* wall_actor = dynamic_cast< entity::Entity_Wall * >( actor );
            auto wall_asset_rect = wall_actor->get_wall_color_map().find( random_wall_color )->second;
            asset_coord_x = wall_asset_rect.at( 0 );
            asset_coord_y = wall_asset_rect.at( 1 );
            asset_coord_width = wall_asset_rect.at( 2 );
            asset_coord_height = wall_asset_rect.at( 3 );
            asset_rect = sf::IntRect( asset_coord_x, asset_coord_y, asset_coord_width, asset_coord_height );
            actor_sprite = new Sprite_Node( *_wall_texture_sheet, asset_rect );
        }
        actor_sprite->setPosition( actor->get_x() * OFFSET, actor->get_y() * OFFSET );
        _scene_layers.push_back( actor_sprite );
        _entities.push_back( entity_actor );
        layers++;
    }

    logger.log( Logger::Level::INFO, "Number of layers loaded: " + std::to_string( layers ) );
}

/**
 * Check whether the board is completed
 * @return whether the board is completed
 */
bool World::is_board_completed() const
{
    return _board.is_completed();
}

/**
 * Move the player up
 * @param pressed Whether the up key is pressed
 */
void World::move_up( bool pressed )
{
    if ( pressed )
    {
        steps_counter++;
    }
    _player_is_moving_up = pressed;
}

/**
 * Move the player down
 * @param pressed Whether the down key is pressed
 */
void World::move_down( bool pressed )
{
    if ( pressed )
    {
        steps_counter++;
    }
    _player_is_moving_down = pressed;
}

/**
 * Move the player left
 * @param pressed Whether the left key is pressed
 */
void World::move_left( bool pressed )
{
    if ( pressed )
    {
        steps_counter++;
    }
    _player_is_moving_left = pressed;
}

/**
 * Move the player right
 * @param pressed Whether the right key is pressed
 */
void World::move_right( bool pressed )
{
    if ( pressed )
    {
        steps_counter++;
    }
    _player_is_moving_right = pressed;
}

/**
 * Setter for the number of resets done throughout the match
 * @param reset_counter The current number of resets
 */
void World::set_reset_counter( int reset_counter )
{
    _reset_counter = reset_counter;
}

/**
 * Getter for the number of resets called
 * @return The number of resets
 */
int World::get_reset_counter() const
{
    return _reset_counter;
}
