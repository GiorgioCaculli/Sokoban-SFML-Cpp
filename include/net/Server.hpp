#ifndef SOKOBAN_SERVER_HPP
#define SOKOBAN_SERVER_HPP

#include <string>

#include <SFML/Network.hpp>

namespace sokoban::net
{
    class Server
    {
    private:
        unsigned short _tcp_port;
        unsigned short _udp_port;
        sf::TcpListener* _tcp_listener;
        sf::UdpSocket* _udp_socket;
        bool init() const;
    public:
        explicit Server( unsigned short tcp_port, unsigned short udp_port );
        Server();
        Server( const Server& server );
        Server& operator=( const Server& server );
        ~Server();
        bool run() const;
    };
}

#endif //SOKOBAN_SERVER_HPP
