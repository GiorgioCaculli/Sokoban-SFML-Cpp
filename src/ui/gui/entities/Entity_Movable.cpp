#include "Entity_Movable.hpp"

using namespace sokoban::ui::gui::entity;

Entity_Movable::Entity_Movable( std::array< float, 4 > asset_coords )
        : Entity( asset_coords )
        , _direction()
{
}

void Entity_Movable::set_direction( float dx, float dy )
{
    _direction.x = dx;
    _direction.y = dy;
}

sf::Vector2f Entity_Movable::get_direction() const
{
    return _direction;
}

void Entity_Movable::update_current( sf::Time dt, Command_Queue &commands )
{
    Entity_Movable::move( _direction * dt.asSeconds() );
}
