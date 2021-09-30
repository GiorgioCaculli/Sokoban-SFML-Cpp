#ifndef SOKOBAN_WORLD_HPP
#define SOKOBAN_WORLD_HPP

#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "scene_node.hpp"
#include "sprite_node.hpp"
#include "player.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

namespace sf
{
    class RenderWindow;
}

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class World : private sf::NonCopyable
            {
            private:
                enum
                {
                    Background,
                    Floor,
                    LayerCount
                };
            public:
                explicit World( sf::RenderWindow &window );

                void update( sf::Time dt );

                void draw();

            private:
                sf::RenderWindow &window;
                sf::View world_view;
                TextureHolder textures;
                SceneNode scene_graph;
                std::array< SceneNode *, LayerCount > scene_layers;
                sf::FloatRect world_bounds;
                sf::Vector2f spawn_position;
                float scroll_speed;
                Player *player;
            private:
                void load_textures();

                void build_scene();
            };
        }
    }
}

#endif //SOKOBAN_WORLD_HPP
