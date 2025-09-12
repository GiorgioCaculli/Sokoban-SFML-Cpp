#include <net/Packet.hpp>

using namespace sokoban::net;

Packet::Packet()
= default;

Packet::Packet( const Packet& p)
= default;

Packet& Packet::operator=( const Packet& p )
{
    if( &p != this )
    {
        /* Copy r packet info */
    }
    return *this;
}

Packet::~Packet()
= default;
