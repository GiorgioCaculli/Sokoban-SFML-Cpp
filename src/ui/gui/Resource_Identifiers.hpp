#ifndef SOKOBAN_RESOURCE_IDENTIFIERS_HPP
#define SOKOBAN_RESOURCE_IDENTIFIERS_HPP

namespace sf
{
    class Texture;

    class Font;
}

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
                    Player,
                    Box,
                    Platform,
                    Wall,
                    Background,
                    TitleScreen,
                };
            }

            namespace Fonts
            {
                enum ID
                {
                    Main,
                    ConnectionII,
                    KodomoRounded,
                    FreeFont,
                    RampartOne,
                };
            }
        }
        template< typename Resource, typename Identifier >
            class Resource_Holder;

        typedef Resource_Holder< sf::Texture, gui::Textures::ID > Texture_Holder;
        typedef Resource_Holder< sf::Font, gui::Fonts::ID > Font_Holder;
    }
}

#endif //SOKOBAN_RESOURCE_IDENTIFIERS_HPP
