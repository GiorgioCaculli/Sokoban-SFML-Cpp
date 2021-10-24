#ifndef SOKOBAN_WORLD_NODE_HPP
#define SOKOBAN_WORLD_NODE_HPP

#include "Scene_Node.hpp"
#include "Sprite_Node.hpp"
#include "../../model/Board.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <vector>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class World_Node
                    : private sf::NonCopyable
            {
            public:
                World_Node( sf::RenderWindow &window, std::string level );
                ~World_Node();
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
                SceneNode *_scene_graph;
                std::vector< SceneNode * > *_scene_layers;
                sf::FloatRect _world_bounds;
                model::Board _board;
                SpriteNode *_player_sprite;
                model::Player *_board_player;
                std::vector< SpriteNode * > *_box_sprites;
                std::vector< model::Box * > *_box_actors;
                void handle_player_input( sf::Keyboard::Key key, bool is_pressed );
                void load_textures();
                void build_scene( const std::string &level );
            };
        }
    }
}

#endif //SOKOBAN_WORLD_NODE_HPP
