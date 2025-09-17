#include <net/Packet.hpp>
#include <net/Client.hpp>

using namespace sokoban::net;

Client::Client( const std::string_view& username )
: gzc::sokoban::net::Client( username )
{
}

Client::Client()
: Client( "SFMLGio" )
{
}

Client::Client( const Client& c )
: Client( c.get_username() )
{
}

Client& Client::operator=( const Client& c )
{
    if( &c != this )
    {
        /* Fetch parent = operator output */
    }
    return *this;
}

Client::~Client()
{
}

bool Client::send_packet( const Packet& p ) const
{
    return false;
}
