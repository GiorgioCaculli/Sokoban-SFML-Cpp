#include "net/Packet.hpp"
#include <net/Client.hpp>

using namespace sokoban::net;

Client::Client()
{
}

Client::~Client()
{
}

bool Client::send_packet( const Packet& p ) const
{
    return false;
}
