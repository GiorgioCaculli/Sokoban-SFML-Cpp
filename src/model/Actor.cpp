#include "Actor.hpp"

#include <utility>

using namespace sokoban::model;

const int SPACE = 64;

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

std::string Actor::get_asset() const
{
    return asset;
}

void Actor::set_asset( std::string asset )
{
    this->asset = std::move( asset );
}

Actor::ID Actor::get_type() const
{
    return Actor::PLAYER;
}

bool Actor::is_left_collision( const Actor *actor ) const
{
    return get_x() - SPACE == actor->get_x() && get_y() == actor->get_y();
}

bool Actor::is_right_collision( const Actor *actor ) const
{
    return get_x() + SPACE == actor->get_x() && get_y() == actor->get_y();
}

bool Actor::is_top_collision( const Actor *actor ) const
{
    return get_y() - SPACE == actor->get_y() && get_x() == actor->get_x();
}

bool Actor::is_bottom_collision( const Actor *actor ) const
{
    return get_y() + SPACE == actor->get_y() && get_x() == actor->get_x();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Actor &actor )
{
    os << "x: " << actor.x << " y: " << actor.y;
    return os;
}

bool Actor::operator==( const Actor &actor ) const
{
    return x == actor.x &&
            y == actor.y &&
            asset == actor.asset;
}

bool Actor::operator!=( const Actor &actor ) const
{
    return !( actor == *this );
}
