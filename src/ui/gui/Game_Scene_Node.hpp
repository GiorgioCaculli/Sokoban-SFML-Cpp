#ifndef SOKOBAN_GAME_SCENE_NODE_HPP
#define SOKOBAN_GAME_SCENE_NODE_HPP

#include "../../model/Board.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class GameSceneNode
                    : private sf::NonCopyable
            {
            private:
                sf::RenderWindow &window;
                sf::View world_view;
                sf::FloatRect world_bounds;
                model::Board *board;
                void load_textures();
                void build_scene();
            public:
                GameSceneNode( sf::RenderWindow &window, std::string level );
                GameSceneNode( sf::RenderWindow &window );
                ~GameSceneNode();
                void update( sf::Time dt );
                void draw();
            };
        }
    }
}

#endif //SOKOBAN_GAMESCENENODE_HPP
