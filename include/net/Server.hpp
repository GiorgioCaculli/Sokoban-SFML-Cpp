#ifndef SOKOBAN_SFML_SERVER_HPP
#define SOKOBAN_SFML_SERVER_HPP

#include <gzc/games/sokoban/net/ServerDedicated.hpp>

#include <SFML/Network.hpp>
#include <sys/types.h>

namespace sokoban::net
{
    class Server : public gzc::sokoban::net::ServerDedicated
    {
    private:
        u_int16_t _tcp_port;
        u_int16_t _udp_port;
        std::shared_ptr< sf::TcpListener > _tcp_listener;
        std::shared_ptr< sf::UdpSocket > _udp_socket;
        bool init() const;
    public:
        explicit Server( u_int16_t tcp_port, u_int16_t udp_port );
        Server();
        Server( const Server& server );
        Server& operator=( const Server& server );
        ~Server() override;
        bool run() const;
    };
}

#endif //SOKOBAN_SFML_SERVER_HPP
