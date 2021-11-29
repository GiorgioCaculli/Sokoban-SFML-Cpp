#ifndef SOKOBAN_STATE_GAME_HPP
#define SOKOBAN_STATE_GAME_HPP

#include "../../model/Board.hpp"

#include "entities/Entity_Box.hpp"
#include "entities/Entity_Platform.hpp"
#include "entities/Entity_Player.hpp"
#include "entities/Entity_Wall.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Game
                    : private sf::NonCopyable
            {
            public:
                State_Game( sf::RenderWindow &window, const std::vector< std::string > &levels, int start_level );
                ~State_Game();
                void update( const sf::Time &dt );
                void draw();
                void process_events();
            private:
                enum class Background_Color
                {
                    CONCRETE,
                    DIRT,
                    GRASS,
                    SAND
                };
                sf::RenderWindow &_window;
                std::string _level;
                bool _player_is_moving_up;
                bool _player_is_moving_down;
                bool _player_is_moving_left;
                bool _player_is_moving_right;
                sf::View _world_view;
                std::vector< sf::Sprite * > _scene_layers;
                sf::FloatRect _world_bounds;
                model::Board _board;
                sf::Sprite *_player_sprite;
                model::Player *_board_player;
                entity::Entity_Player *_player_entity;
                std::vector< sf::Sprite * > _box_sprites;
                std::vector< model::Box * > _box_actors;
                std::vector< entity::Entity_Box * > _box_entities;
                std::vector< entity::Entity * > _entities;
                sf::Music music;
                sf::SoundBuffer step_buffer;
                sf::Sound step_sound;
                sf::SoundBuffer box_move_buffer;
                sf::Sound box_move_sound;
                sf::Texture *_box_texture_sheet;
                sf::Texture *_platform_texture_sheet;
                sf::Texture *_wall_texture_sheet;
                sf::Texture *_player_texture_sheet;
                sf::Texture *_background_texture;
                sf::Font *_font;
                sf::Text *_text;
                void handle_player_input( sf::Keyboard::Key key, bool is_pressed );
                void load_textures();
                void build_scene( const std::string &level );
                void reset_board();
            };
        }
    }
}

#endif //SOKOBAN_STATE_GAME_HPP
