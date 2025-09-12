#ifndef SOKOBAN_SFML_PACKET_HPP
#define SOKOBAN_SFML_PACKET_HPP

namespace sokoban::net
{
    class Packet
    {
    public:
        Packet();
        Packet( const Packet &p );
        Packet& operator=( const Packet &p );
        ~Packet();
    };
}

#endif //SOKOBAN_SFML_PACKET_HPP
