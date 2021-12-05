#ifndef SOKOBAN_ENTITY_MOVABLE_HPP
#define SOKOBAN_ENTITY_MOVABLE_HPP

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
                class Entity_Movable
                        : public Entity
                {
                public:
                    explicit Entity_Movable( std::array< float, 4 > asset_coords );
                    void set_direction( float dx, float dy );
                    sf::Vector2f get_direction() const;
                    void update_current( sf::Time dt, Command_Queue &commands ) override;
                private:
                    sf::Vector2f _direction;
                };
            }
        }
    }
}

#endif //SOKOBAN_ENTITY_MOVABLE_HPP
