#ifndef SOKOBAN_STATE_GAME_HPP
#define SOKOBAN_STATE_GAME_HPP

#include "../../model/Board.hpp"

#include <SFML/System/NonCopyable.hpp>
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
                State_Game( sf::RenderWindow &window, const std::string &level );
                ~State_Game();
                void update( const sf::Time &dt );
                void draw();
                void process_events();
            private:
                sf::RenderWindow &_window;
                const std::string _level;
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
                std::vector< sf::Sprite * > _box_sprites;
                std::vector< model::Box * > _box_actors;
                sf::Music music;
                sf::SoundBuffer step_buffer;
                sf::Sound step_sound;
                sf::SoundBuffer box_move_buffer;
                sf::Sound box_move_sound;
                sf::Texture *_base_sokoban_texture;
                sf::Texture *_background_texture;
                void handle_player_input( sf::Keyboard::Key key, bool is_pressed );
                void load_textures();
                void build_scene( const std::string &level );
            };
        }
    }
}

#endif //SOKOBAN_STATE_GAME_HPP
