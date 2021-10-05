#ifndef SOKOBAN_RESOURCE_IDENTIFIERS_HPP
#define SOKOBAN_RESOURCE_IDENTIFIERS_HPP

#include <SFML/Graphics/Texture.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            namespace Textures
            {
                enum ID
                {
                    Wall,
                    Box,
                    Platform,
                    Player_North,
                    Player_South,
                    Player_East,
                    Player_West,
                    Floor
                };
            }
            template< typename Resource, typename Identifier >
                class ResourceHolder;

            typedef ResourceHolder< sf::Texture, Textures::ID > TextureHolder;
        }
    }
}

#endif //SOKOBAN_RESOURCE_IDENTIFIERS_HPP
