#ifndef SOKOBAN_WORLD_NODE_HPP
#define SOKOBAN_WORLD_NODE_HPP

#include "Scene_Node.hpp"
#include "Sprite_Node.hpp"
#include "../../model/Board.hpp"

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
            private:
                sf::RenderWindow &window;
                sf::View world_view;
                std::vector< SceneNode * > *scene_layers;
                sf::FloatRect world_bounds;
                model::Board *board;
                void load_textures();
                void build_scene();
            };
        }
    }
}

#endif //SOKOBAN_WORLD_NODE_HPP
