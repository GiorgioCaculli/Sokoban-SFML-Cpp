#include <gui/entities/Entity_Player.hpp>

using namespace sokoban::ui::gui::entity;

/**
 * Default constructor for the Player entity
 * @param x The coordinates on the X axis
 * @param y The coordinates on the Y axis
 */
Entity_Player::Entity_Player( float x, float y )
    : Player( x, y )
{

    constexpr float SPRITE_SHEET_PLACEMENT_Y_COORDINATE = 0;

    /* TODO: Apply FOR loop + mapping for cleaner generation, need to overcome the single naming issue (mapping) */
    std::array< float, 4 > character_facing_west = {
        SPRITE_SHEET_SPRITE_OFFSET * 0, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    std::array< float, 4 > character_walking_west = {
        SPRITE_SHEET_SPRITE_OFFSET * 1, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };

    std::array< float, 4 > character_facing_east = {
        SPRITE_SHEET_SPRITE_OFFSET * 2, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    std::array< float, 4 > character_walking_east = {
        SPRITE_SHEET_SPRITE_OFFSET * 3, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };

    std::array< float, 4 > character_facing_south = {
        SPRITE_SHEET_SPRITE_OFFSET * 4, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };

    std::array< float, 4 > character_walking_south_right_step = {
        SPRITE_SHEET_SPRITE_OFFSET * 5, 0, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    std::array< float, 4 > character_walking_south_left_step = {
        SPRITE_SHEET_SPRITE_OFFSET * 6, 0, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };

    std::array< float, 4 > character_facing_north = {
        SPRITE_SHEET_SPRITE_OFFSET * 7, 0, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    std::array< float, 4 > character_walking_north_right_step = {
        SPRITE_SHEET_SPRITE_OFFSET * 8, 0, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    std::array< float, 4 > character_walking_north_left_step = {
        SPRITE_SHEET_SPRITE_OFFSET * 9, 0, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };

    const std::array< float, 4 > player_asset_north = character_facing_north;
    const std::array< float, 4 > player_asset_south = character_facing_south;
    const std::array< float, 4 > player_asset_east = character_facing_east;
    const std::array< float, 4 > player_asset_west = character_facing_west;
    _player_face_map = std::map< Face, std::array< float, 4 > >
    {
        { Face::NORTH, player_asset_north }, { Face::SOUTH, player_asset_south }, { Face::EAST, player_asset_east },
        { Face::WEST, player_asset_west }
    };
}

/**
 * Copy constructor for the player entity
 * @param entity The entity we wish to get the information from
 */
Entity_Player::Entity_Player( const Entity_Player& entity )
    : Entity_Player( entity.get_x(), entity.get_y() )
{
    set_asset_coordinates( entity.get_asset_coordinates() );
    _player_face_map = entity._player_face_map;
}

/**
 * Redefinition of the = operator
 * @param entity The entity we wish to get the information from
 * @return The new instance of a place with the copied information
 */
Entity_Player& Entity_Player::operator=( const Entity_Player& entity )
{
    if ( &entity != this )
    {
        Player::operator=( entity );
        Entity::operator=( entity );
        set_asset_coordinates( entity.get_asset_coordinates() );
        _player_face_map = entity._player_face_map;
    }
    return *this;
}

/**
 * Default destructor for the entity player
 */
Entity_Player::~Entity_Player()
= default;

/**
 * Textual output containing the Player's information
 * @return Text containing the player's information
 */
std::string Entity_Player::to_string() const
{
    return Player::to_string();
}

/**
 * Getter for the mapper containing the coordinates of each asset based on where the player is looking
 * @return The mapper containing the assets
 */
const std::map< Entity_Player::Face, std::array< float, 4 > >& Entity_Player::get_player_face_map() const
{
    return _player_face_map;
}
