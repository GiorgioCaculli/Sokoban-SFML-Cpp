#ifndef SOKOBAN_ENTITY_HPP
#define SOKOBAN_ENTITY_HPP

#include "../Scene_Node.hpp"

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
                class Entity
                        : public Scene_Node
                {
                public:
                    explicit Entity( std::array< float, 4 > asset_coords );
                    Entity( const Entity &entity );
                    Entity &operator=( const Entity &entity );
                    ~Entity() override;
                    std::array< float, 4 > get_asset_coords() const;
                    void set_asset_coords( std::array< float, 4 > asset_coords );
                    void update_current( sf::Time dt, Command_Queue &commands ) override;
                private:
                    std::array< float, 4 > _assets_coords;
                };
            }
        }
    }
}

#endif //SOKOBAN_ENTITY_HPP
