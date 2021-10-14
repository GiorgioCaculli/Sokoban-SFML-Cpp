#ifndef SOKOBAN_GAME_SCENE_NODE_HPP
#define SOKOBAN_GAME_SCENE_NODE_HPP

#include "World_Node.hpp"

#include <SFML/System/NonCopyable.hpp>
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
                World_Node *world;
            public:
                GameSceneNode( sf::RenderWindow &window, std::string level );
                explicit GameSceneNode( sf::RenderWindow &window );
                ~GameSceneNode();
                void update( sf::Time dt );
                void draw();
                void process_events();
            };
        }
    }
}

#endif //SOKOBAN_GAME_SCENE_NODE_HPP
