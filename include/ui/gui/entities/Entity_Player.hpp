#ifndef SOKOBAN_ENTITY_PLAYER_HPP
#define SOKOBAN_ENTITY_PLAYER_HPP

#include <gzc/games/sokoban/core/Player.hpp>
#include <ui/gui/entities/Entity_Movable.hpp>

#include <SFML/Window/Event.hpp>

#include <map>
#include <array>
#include <string>
#include <ostream>


namespace sokoban::ui::gui::entity
{
    class Entity_Player
            : public sokoban::core::Player
              , public Entity_Movable
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

        Entity_Player( const Entity_Player& entity );

        Entity_Player& operator=( const Entity_Player& entity );

        ~Entity_Player() override;

        std::string to_string() const override;

        const std::map< Face, std::array< float, 4 > >& get_player_face_map() const;

    private:
        /** Mapper containing the coordinates of each asset based on the direction the player is looking */
        std::map< Face, std::array< float, 4 > > _player_face_map;
    };
}


#endif //SOKOBAN_ENTITY_PLAYER_HPP
