#include "Movable.hpp"

#include <utility>

using namespace sokoban::model;

/*
 * Tout comme la classe Actor, l'objet 'moveable' doit aussi instancier les coordonnées X et Y
 * ainsi que l'asset qui le représentera graphiquement.
 */
Movable::Movable( int x, int y, std::array< int, 4 > asset_coords )
        : Actor( x, y, asset_coords )
{
}

Movable::Movable( const Movable &movable )
        : Movable( movable.get_x(), movable.get_y(), movable.get_asset_coords() )
{
}

Movable &Movable::operator=( const Movable &movable )
{
    if( &movable != this )
    {
        set_x( movable.get_x() );
        set_y( movable.get_y() );
        set_asset_coords( movable.get_asset_coords() );
    }
    return *this;
}

void Movable::move( int x, int y )
{
    set_x( get_x() + x );
    set_y( get_y() + y );
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Movable &movable )
{
    os << static_cast<const Actor &>(movable);
    return os;
}

Actor::ID Movable::get_type() const
{
    return Actor::PLAYER;
}
