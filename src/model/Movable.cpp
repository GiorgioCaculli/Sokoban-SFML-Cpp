#include "Movable.hpp"

#include <sstream>
#include <utility>

using namespace sokoban::model;

/*
 * Tout comme la classe Actor, l'objet 'moveable' doit aussi instancier les coordonnées X et Y
 * ainsi que l'asset qui le représentera graphiquement.
 */
Movable::Movable( float x, float y, std::array< float, 4 > asset_coords )
        : Actor( x, y, asset_coords )
{
}

Movable::Movable( const Movable &movable )
        : Movable( movable.get_x(), movable.get_y(), movable.get_asset_coords() )
{
}

Movable &Movable::operator=( const Movable &movable )
{
    if ( &movable != this )
    {
        set_x( movable.get_x() );
        set_y( movable.get_y() );
        set_asset_coords( movable.get_asset_coords() );
    }
    return *this;
}

void Movable::move( float x, float y )
{
    set_x( get_x() + x );
    set_y( get_y() + y );
}

std::string Movable::to_string() const
{
    std::stringstream ss;
    ss << Actor::to_string();
    return ss.str();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Movable &movable )
{
    os << movable.to_string();
    return os;
}
