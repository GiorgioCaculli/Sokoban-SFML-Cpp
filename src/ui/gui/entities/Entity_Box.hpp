#ifndef SOKOBAN_ENTITY_BOX_HPP
#define SOKOBAN_ENTITY_BOX_HPP

#include "../../../model/Box.hpp"
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

                class Entity_Box
                          : public model::Box
                            , public Entity
                {

                public:
                    enum class Color
                    {
                        BEIGE_LIGHT,
                        BLACK_LIGHT,
                        BLUE_LIGHT,
                        BROWN_LIGHT,
                        BEIGE_DARK,
                        BLACK_DARK,
                        BLUE_DARK,
                        BROWN_DARK,
                        WHITE_DARK,
                        PURPLE_DARK,
                        RED_DARK,
                        YELLOW_DARK,
                        WHITE_LIGHT,
                        PURPLE_LIGHT,
                        RED_LIGHT,
                        YELLOW_LIGHT
                    };
                    Entity_Box( float x, float y );
                    Entity_Box( const Entity_Box &box );
                    Entity_Box &operator=( const Entity_Box &box );
                    ~Entity_Box() override;
                    ID get_type() const override;
                    std::string to_string() const override;
                    friend std::ostream &operator<<( std::ostream &os, const Entity_Box &box );
                    const std::map< Color, std::array< float, 4>> &get_box_color_map() const;
                private:
                    std::map< Color, std::array< float, 4 > > _box_color_map;
                };
            }
        }
    }
}

#endif //SOKOBAN_ENTITY_BOX_HPP
