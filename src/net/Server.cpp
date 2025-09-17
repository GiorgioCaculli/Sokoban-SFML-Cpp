#include <gzc/games/sokoban/net/ServerDedicated.hpp>
#include <net/Server.hpp>
#include <sys/types.h>

using namespace sokoban::net;

Server::Server( u_int16_t tcp_port, u_int16_t udp_port )
    : gzc::sokoban::net::ServerDedicated( "SFML", "localhost", tcp_port)
    , _tcp_port( tcp_port )
    , _udp_port( udp_port )
{
    _tcp_listener = std::make_shared< sf::TcpListener >();
    _udp_socket = std::make_shared< sf::UdpSocket >();
}

Server::Server()
    : Server( 22497, 23497 )
{
}

Server::Server( const Server& server )
    : Server( server._tcp_port, server._udp_port )
{
}

Server& Server::operator=( const Server& server )
{
    if ( this != &server )
    {
        this->_tcp_listener = server._tcp_listener;
        this->_udp_socket = server._udp_socket;
    }
    return *this;
}

Server::~Server()
= default;

bool Server::init() const
{
    if ( _tcp_listener->listen( _tcp_port ) != sf::Socket::Status::Done )
    {
        return false;
    }
    if ( _udp_socket->bind( _udp_port ) != sf::Socket::Status::Done )
    {
        return false;
    }
    return true;
}

bool Server::run() const
{
    return init();
}
