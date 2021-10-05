#include "Actor.hpp"

using namespace sokoban::model;

Actor::Actor( int x, int y )
        : x( x )
          , y( y )
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
