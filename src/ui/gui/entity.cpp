#include "entity.hpp"

using namespace sokoban::ui::gui;

void Entity::set_velocity( sf::Vector2f velocity )
{
    this->velocity = velocity;
}

void Entity::set_velocity( float vx, float vy )
{
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2f Entity::get_velocity() const
{
    return velocity;
}

void Entity::update_current( sf::Time dt )
{
    std::move( velocity * dt.asSeconds() );
}
