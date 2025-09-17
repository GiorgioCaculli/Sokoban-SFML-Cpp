#ifndef SOKOBAN_SFML_CLIENT_HPP
#define SOKOBAN_SFML_CLIENT_HPP

#include <string>
#include <string_view>
#include <gzc/games/sokoban/net/Client.hpp>
#include <net/Packet.hpp>

namespace sokoban::net
{
    class Client : public gzc::sokoban::net::Client
    {
    private:
        Packet _p;
    public:
        explicit Client( const std::string_view& username );
        Client();
        Client( const Client& c );
        Client& operator=( const Client& c );
        ~Client();
        bool send_packet( const Packet& p ) const;
    };
}

#endif //SOKOBAN_SFML_CLIENT_HPP
