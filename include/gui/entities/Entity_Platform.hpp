#ifndef SOKOBAN_ENTITY_PLATFORM_HPP
#define SOKOBAN_ENTITY_PLATFORM_HPP

#include <gzc/games/sokoban/core/Platform.hpp>
#include <gui/entities/Entity.hpp>

#include <map>
#include <array>
#include <string>


namespace sokoban::ui::gui::entity
{
    class Entity_Platform final
            : public gzc::sokoban::core::Platform
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

        Entity_Platform( const Entity_Platform& entity );

        Entity_Platform& operator=( const Entity_Platform& entity );

        ~Entity_Platform() override;

        std::string to_string() const override;

        const std::map< Color, std::array< float, 4 > >& get_platform_color_map() const;

    private:
        /** Mapper containing the coordinates of each asset based on the color */
        std::map< Color, std::array< float, 4 > > _platform_color_map;
    };
}


#endif //SOKOBAN_ENTITY_PLATFORM_HPP
