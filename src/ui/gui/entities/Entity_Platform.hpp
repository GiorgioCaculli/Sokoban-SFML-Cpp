#ifndef SOKOBAN_ENTITY_PLATFORM_HPP
#define SOKOBAN_ENTITY_PLATFORM_HPP

#include "../../../model/Platform.hpp"
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
                class Entity_Platform
                        : public model::Platform
                        , public Entity
                {
                public:
                    enum class Color
                    {
                        BEIGE,
                        BLACK,
                        BLUE,
                        BROWN,
                        WHITE,
                        PURPLE,
                        RED,
                        YELLOW
                    };
                    Entity_Platform( float x, float y );
                    Entity_Platform( const Entity_Platform &entity );
                    Entity_Platform &operator=( const Entity_Platform &entity );
                    ~Entity_Platform() override;
                    std::string to_string() const;
                    const std::map< Color, std::array< float, 4>> &get_platform_color_map() const;
                    friend std::ostream &operator<<( std::ostream &os, const Entity_Platform &entity );
                private:
                    /** Mapper containing the coordinates of each asset based on the color */
                    std::map< Color, std::array< float, 4 > > _platform_color_map;
                };
            }
        }
    }
}

#endif //SOKOBAN_ENTITY_PLATFORM_HPP
