#ifndef SOKOBAN_ENTITY_MOVABLE_HPP
#define SOKOBAN_ENTITY_MOVABLE_HPP

#include <ui/gui/entities/Entity.hpp>

#include <array>


namespace sokoban::ui::gui::entity
{
    class Entity_Movable
            : public Entity
    {
    public:
        explicit Entity_Movable( std::array< float, 4 > asset_coordinates );
        Entity_Movable();
        Entity_Movable( Entity_Movable&& other ) noexcept;
        ~Entity_Movable() override;
        void set_direction( float dx, float dy );
        sf::Vector2f get_direction() const;
        void update_current( sf::Time dt, Command_Queue& commands ) override;
    private:
        /** The direction the Entity has to move to */
        sf::Vector2f _direction{};
    };
}


#endif //SOKOBAN_ENTITY_MOVABLE_HPP
