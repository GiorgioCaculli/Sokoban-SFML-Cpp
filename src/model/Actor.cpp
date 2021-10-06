#include "Actor.hpp"

#include <utility>

using namespace sokoban::model;

Actor::Actor( int x, int y, std::string asset )
        : x( x )
          , y( y )
          , asset( std::move( asset ) )
{

}
Actor::Actor( const Actor &actor )
        : x( actor.x )
          , y( actor.y )
{

}
Actor::~Actor() = default;

int Actor::get_x() const
{
    return x;
}
void Actor::set_x( int x )
{
    this->x = x;
}
int Actor::get_y() const
{
    return y;
}
void Actor::set_y( int y )
{
    this->y = y;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Actor &actor )
{
    os << "x: " << actor.x << " y: " << actor.y;
    return os;
}

Actor::ID Actor::get_type() const
{
    return Actor::PLAYER;
}

std::string Actor::get_asset() const
{
    return asset;
}

void Actor::set_asset( std::string asset )
{
    this->asset = std::move( asset );
}
