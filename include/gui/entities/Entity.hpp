#ifndef SOKOBAN_ENTITY_HPP
#define SOKOBAN_ENTITY_HPP

#include <gui/Scene_Node.hpp>

#include <array>

namespace sokoban::ui::gui::entity
{
    class Entity
            : public Scene_Node
    {
    protected:
        const float SPRITE_SHEET_SPRITE_OFFSET = 64;
        const uint8_t SPRITE_SHEET_NUMBER_OF_COORDINATES = 4;
    private:
        /** The asset's coordinates on the spritesheet */
        std::array< float, 4 > _assets_coordinates;
    public:
        explicit Entity( std::array< float, 4 > asset_coordinates );
        Entity();
        Entity( const Entity& entity );
        Entity& operator=( const Entity& entity );
        ~Entity() override;
        std::array< float, 4 > get_asset_coordinates() const;
        void set_asset_coordinates( std::array< float, 4 > asset_coordinates );
        void update_current( sf::Time dt, Command_Queue& commands ) override;
    };
}


#endif //SOKOBAN_ENTITY_HPP
