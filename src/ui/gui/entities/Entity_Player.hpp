#ifndef SOKOBAN_ENTITY_PLAYER_HPP
#define SOKOBAN_ENTITY_PLAYER_HPP

#include "../../../model/Player.hpp"
#include "Entity.hpp"

#include <map>
#include <array>
#include <string>
#include <ostream>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            namespace entity
            {
                class Entity_Player
                        : public model::Player
                          , public Entity
                {
                public:
                    enum class Face
                    {
                        NORTH,
                        SOUTH,
                        EAST,
                        WEST
                    };
                    Entity_Player( float x, float y );
                    Entity_Player( const Entity_Player &entity );
                    Entity_Player &operator=( const Entity_Player &entity );
                    ~Entity_Player() override;
                    std::string to_string() const;
                    const std::map< Face, std::array< float, 4>> &get_player_face_map() const;
                    friend std::ostream &operator<<( std::ostream &os, const Entity_Player &entity );
                private:
                    std::map< Face, std::array< float, 4 > > _player_face_map;
                };
            }
        }
    }
}

#endif //SOKOBAN_ENTITY_PLAYER_HPP
