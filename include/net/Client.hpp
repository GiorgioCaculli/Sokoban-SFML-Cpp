#ifndef SOKOBAN_SFML_CLIENT_HPP
#define SOKOBAN_SFML_CLIENT_HPP

#include <net/Packet.hpp>
#include <gzc/games/sokoban/net/Client.hpp>

namespace sokoban::net
{
    class Client : public gzc::sokoban::net::Client
    {
    private:
        Packet _p;
    public:
        Client();
        Client( const Client& c );
        Client& operator=( const Client& c );
        ~Client();
        bool send_packet( const Packet& p ) const;
    };
}

#endif //SOKOBAN_SFML_CLIENT_HPP
