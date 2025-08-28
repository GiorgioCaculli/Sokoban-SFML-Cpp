#ifndef SOKOBAN_WORLD_HPP
#define SOKOBAN_WORLD_HPP

#include <ui/Resource_Holder.hpp>
#include <ui/gui/Resource_Identifiers.hpp>
#include <ui/gui/Scene_Node.hpp>
#include <ui/gui/Sprite_Node.hpp>
#include <ui/gui/entities/Entity.hpp>
#include <ui/gui/entities/Entity_Box.hpp>
#include <ui/gui/entities/Entity_Wall.hpp>
#include <ui/gui/entities/Entity_Player.hpp>
#include <ui/gui/entities/Entity_Platform.hpp>
#include <ui/gui/Sound_Player.hpp>
#include <gzc/games/sokoban/core/Board.hpp>

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


namespace sokoban::ui::gui
{
    class World
            : private sf::NonCopyable
    {
    public:
        World( sf::RenderTarget& target, const core::Board& board, Font_Holder& fonts, Sound_Player& sounds );

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
        /**
         * The various background colors
         */
        enum class Background_Color
        {
            CONCRETE,
            DIRT,
            GRASS,
            SAND
        };

        sf::RenderTarget& _target; /** The window that will display the various components */
        sf::View _world_view; /** The globally defined world view */
        Texture_Holder _textures; /** Default texture holder */
        Font_Holder& _fonts; /** Default font holder */
        Sound_Player& _sounds; /** Default Sound Player */
        Scene_Node _scene_graph; /** Main scene node */
        std::vector< Scene_Node * > _scene_layers; /** Various Scene layers */
        bool _player_is_moving_up; /** Whether the player is moving up */
        bool _player_is_moving_down; /** Whether the player is moving down */
        bool _player_is_moving_left; /** Whether the player is moving left */
        bool _player_is_moving_right; /** Whether the player is moving right */
        sf::FloatRect _world_bounds; /** The accessible limits of the window */
        core::Board _board; /** The Board containing all the actors */
        Sprite_Node* _player_sprite; /** The player sprite */
        core::Player* _board_player; /** The player within the board */
        entity::Entity_Player* _player_entity;
        /** The player entity containing the various assets coordinates */
        std::vector< Sprite_Node * > _box_sprites; /** The various box sprites */
        std::vector< core::Box * > _box_actors; /** The various box actors within the board */
        std::vector< entity::Entity_Box * > _box_entities;
        /** The various box entities containing the assets' coordinates */
        std::vector< entity::Entity * > _entities; /** The entirety of the entities present in the world */
        sf::Texture* _box_texture_sheet; /** The box texture */
        sf::Texture* _platform_texture_sheet; /** The platform texture */
        sf::Texture* _wall_texture_sheet; /** The wall texture */
        sf::Texture* _player_texture_sheet; /** The player texture */
        sf::Texture* _background_texture; /** The background texture */
        sf::Text* _text; /** The visually visible text */
        int _reset_counter; /** The amount of resets */
        void load_textures();

        void build_scene();
    };
}


#endif //SOKOBAN_WORLD_HPP
