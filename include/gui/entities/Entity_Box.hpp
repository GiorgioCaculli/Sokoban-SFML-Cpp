#ifndef SOKOBAN_ENTITY_BOX_HPP
#define SOKOBAN_ENTITY_BOX_HPP

#include <gzc/games/sokoban/core/Box.hpp>
#include <gui/entities/Entity_Movable.hpp>

#include <map>
#include <array>
#include <string>


namespace sokoban::ui::gui::entity
{
    class Entity_Box final
            : public gzc::sokoban::core::Box
              , public Entity_Movable
    {
    public:
        /** The various colors of a box */
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

        Entity_Box( const Entity_Box& box );

        Entity_Box& operator=( const Entity_Box& box );

        ~Entity_Box() override;

        ID get_type() const override;

        std::string to_string() const override;

        const std::map< Color, std::array< float, 4 > >& get_box_color_map() const;

    private:
        /** Mapper containing the coordinates of each asset based on the color */
        std::map< Color, std::array< float, 4 > > _box_color_map;
    };
}


#endif //SOKOBAN_ENTITY_BOX_HPP
