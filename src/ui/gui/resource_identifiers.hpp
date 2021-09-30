#ifndef SOKOBAN_RESOURCE_IDENTIFIERS_HPP
#define SOKOBAN_RESOURCE_IDENTIFIERS_HPP

namespace sf
{
    class Texture;
}
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
        Background
    };
}

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            template< typename Resource, typename Identifier >
            class ResourceHolder;

            typedef ResourceHolder< sf::Texture, Textures::ID > TextureHolder;
        }
    }
}

#endif //SOKOBAN_RESOURCE_IDENTIFIERS_HPP
