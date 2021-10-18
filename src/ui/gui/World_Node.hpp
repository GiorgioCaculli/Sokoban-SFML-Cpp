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
                explicit World_Node( sf::RenderWindow &window );
                World_Node( sf::RenderWindow &window, std::string level );
                ~World_Node();
                void update( sf::Time dt );
                void draw();
                void process_events();
            private:
                sf::RenderWindow &window;
                bool player_is_moving_up;
                bool player_is_moving_down;
                bool player_is_moving_left;
                bool player_is_moving_right;
                void handle_player_input( sf::Keyboard::Key key, bool is_pressed );
                sf::View world_view;
                SceneNode *scene_graph;
                std::vector< SceneNode * > *scene_layers;
                sf::FloatRect world_bounds;
                model::Board *board;
                SpriteNode *player_sprite;
                model::Actor *board_player;
                std::vector< SpriteNode * > *box_sprites;
                std::vector< model::Actor * > *box_actors;
                void load_textures();
                void build_scene( const std::string &level );
            };
        }
    }
}

#endif //SOKOBAN_WORLD_NODE_HPP
