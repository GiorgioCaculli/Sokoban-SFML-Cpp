#include <ui/gui/entities/Entity.hpp>

#include <cassert>

using namespace sokoban::ui::gui::entity;

/**
 * Entity constructor meant to initialize the asset's coordinates on the sprite sheet
 */
Entity::Entity( std::array< float, 4 > asset_coords )
    : _assets_coords( asset_coords )
{
}

/**
 * Copy constructor for the entity
 * @param entity The entity to copy the information from
 */
Entity::Entity( const Entity& entity )
    : Entity( entity._assets_coords )
{
}

/**
 * Redefinition of the = operator
 * @param entity The entity to copy the information from
 * @return The new instance of the entity with the copied information
 */
Entity& Entity::operator=( const Entity& entity )
{
    if ( &entity != this )
    {
        _assets_coords = entity._assets_coords;
    }
    return *this;
}

/**
 * Default entity destructor
 */
Entity::~Entity()
= default;

/**
 * Getter for the assets coordinates
 * @return Array of floats containing the asset's coordinates
 */
std::array< float, 4 > Entity::get_asset_coords() const
{
    return _assets_coords;
}

/**
 * Setter for the asset's coordinates
 * @param asset_coords The assets to retrieve and set as new
 */
void Entity::set_asset_coords( std::array< float, 4 > asset_coords )
{
    _assets_coords = asset_coords;
}

/**
 * Visual real-time update of a movable entity along with its commands
 */
void Entity::update_current( sf::Time dt, Command_Queue& commands )
{
    ( void ) dt;
    ( void ) commands;
}
