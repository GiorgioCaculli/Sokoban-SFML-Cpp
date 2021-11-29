#ifndef SOKOBAN_ENTITY_WALL_HPP
#define SOKOBAN_ENTITY_WALL_HPP

#include "../../../model/Wall.hpp"
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
                class Entity_Wall
                        : public model::Wall
                          , public Entity
                {
                public:
                    enum class Color
                    {
                        BEIGE,
                        BLACK,
                        BROWN,
                        WHITE
                    };
                    Entity_Wall( float x, float y );
                    Entity_Wall( const Entity_Wall &entity );
                    Entity_Wall &operator=( const Entity_Wall &entity );
                    ~Entity_Wall() override;
                    std::string to_string() const;
                    const std::map< Color, std::array< float, 4>> &get_wall_color_map() const;
                    friend std::ostream &operator<<( std::ostream &os, const Entity_Wall &entity );
                private:
                    std::map< Color, std::array< float, 4 > > _wall_color_map;
                };
            }
        }
    }
}

#endif //SOKOBAN_ENTITY_WALL_HPP
