#include <map>
#include <SFML/Graphics/Color.hpp>
#include <ui/gui/entities/Entity_Movable.hpp>

using namespace sokoban::ui::gui::entity;


/**
 * Constructor for a movable entity
 * @param asset_coordinates The asset's coordinates
 */
Entity_Movable::Entity_Movable( const std::array< float, 4 > asset_coordinates )
    : Entity( asset_coordinates )
{
}

Entity_Movable::Entity_Movable()
    : Entity_Movable( std::array< float, 4 >() )
{
}

Entity_Movable::Entity_Movable( Entity_Movable&& other ) noexcept
    : Entity_Movable( other.get_asset_coordinates() )
{
}

Entity_Movable::~Entity_Movable()
{
}

/**
 * The direction where the entity moves to
 * @param dx Movement distance of the X axis
 * @param dy Movement distance of the Y axis
 */
void Entity_Movable::set_direction( const float dx, const float dy )
{
    _direction.x = dx;
    _direction.y = dy;
}

/**
 * Getter for the direction where the entity moves to
 * @return The vector containing the X and Y axis of the direction
 */
sf::Vector2f Entity_Movable::get_direction() const
{
    return _direction;
}

/**
 * Visual real-time update of a movable entity along with its commands
 */
void Entity_Movable::update_current( const sf::Time dt, Command_Queue& commands )
{
    move( _direction * dt.asSeconds() );
    ( void ) commands;
}
