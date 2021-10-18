#include "Movable.hpp"

#include <utility>

using namespace sokoban::model;

/*
 * Tout comme la classe Actor, l'objet 'moveable' doit aussi instancier les coordonnées X et Y
 * ainsi que l'asset qui le représentera graphiquement.
 */
Movable::Movable( int x, int y, std::string asset )
        : Actor( x, y, std::move( asset ) )
{

}
Movable::Movable( const Movable &movable )
        : Actor( movable )
{

}
Movable::~Movable() = default;

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
