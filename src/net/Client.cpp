#include <net/Packet.hpp>
#include <net/Client.hpp>

using namespace sokoban::net;

Client::Client()
= default;

Client::Client( const Client& c )
= default;

Client& Client::operator=( const Client& c )
{
    if( &c != this )
    {
        /* Copy client info */
    }
    return *this;
}

Client::~Client()
= default;

bool Client::send_packet( const Packet& p ) const
{
    return false;
}
