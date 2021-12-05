#ifndef SOKOBAN_WORLD_HPP
#define SOKOBAN_WORLD_HPP

#include "../Resource_Holder.hpp"
#include "Resource_Identifiers.hpp"
#include "Scene_Node.hpp"
#include "Sprite_Node.hpp"
#include "entities/Entity.hpp"
#include "entities/Entity_Box.hpp"
#include "entities/Entity_Wall.hpp"
#include "entities/Entity_Player.hpp"
#include "entities/Entity_Platform.hpp"
#include "Sound_Player.hpp"
#include "../../model/Board.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

#include <queue>
#include <vector>

namespace sf
{
    class RenderTarget;
}

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class World
        : private sf::NonCopyable
            {
            public:
                World( sf::RenderTarget &target, const model::Board &board, Font_Holder &fonts, Sound_Player &sounds );
                ~World();
                void update( sf::Time dt );
                void draw();
                bool is_board_completed() const;
                void move_up( bool pressed );
                void move_down( bool pressed );
                void move_left( bool pressed );
                void move_right( bool pressed );
                void set_reset_counter( int reset_counter );
                int get_reset_counter() const;
            private:
                enum class Background_Color
                {
                    CONCRETE,
                    DIRT,
                    GRASS,
                    SAND
                };
                sf::RenderTarget &_target;
                sf::View _world_view;
                Texture_Holder _textures;
                Font_Holder &_fonts;
                Sound_Player &_sounds;
                Scene_Node _scene_graph;
                std::vector< Scene_Node * > _scene_layers;
                bool _player_is_moving_up;
                bool _player_is_moving_down;
                bool _player_is_moving_left;
                bool _player_is_moving_right;
                sf::FloatRect _world_bounds;
                model::Board _board;
                Sprite_Node *_player_sprite;
                model::Player *_board_player;
                entity::Entity_Player *_player_entity;
                std::vector< Sprite_Node * > _box_sprites;
                std::vector< model::Box * > _box_actors;
                std::vector< entity::Entity_Box * > _box_entities;
                std::vector< entity::Entity * > _entities;
                sf::Texture *_box_texture_sheet;
                sf::Texture *_platform_texture_sheet;
                sf::Texture *_wall_texture_sheet;
                sf::Texture *_player_texture_sheet;
                sf::Texture *_background_texture;
                sf::Text *_text;
                int _reset_counter;
                void load_textures();
                void build_scene();
            };
        }
    }
}

#endif //SOKOBAN_WORLD_HPP
