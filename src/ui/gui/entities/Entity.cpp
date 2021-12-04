#include "Entity.hpp"

#include <cassert>

using namespace sokoban::ui::gui::entity;

Entity::Entity( std::array< float, 4 > asset_coords )
: _assets_coords( asset_coords )
{
}

Entity::Entity( const Entity &entity )
: Entity( entity._assets_coords )
{
}

Entity &Entity::operator=( const Entity &entity )
{
    if( &entity != this )
    {
        _assets_coords = entity._assets_coords;
    }
    return *this;
}

Entity::~Entity()
= default;

std::array< float, 4 > Entity::get_asset_coords() const
{
    return _assets_coords;
}

void Entity::set_asset_coords( std::array< float, 4 > asset_coords )
{
    _assets_coords = asset_coords;
}

void Entity::update_current( sf::Time dt, Command_Queue &commands )
{
}
