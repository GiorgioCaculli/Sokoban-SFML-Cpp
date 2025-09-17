#ifndef SOKOBAN_RESOURCE_IDENTIFIERS_HPP
#define SOKOBAN_RESOURCE_IDENTIFIERS_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>

//namespace sf
//{
//    class Texture;
//    class Font;
//    class Shader;
//    class SoundBuffer;
//}


namespace sokoban::ui
{
    namespace gui
    {
        namespace Textures
        {
            /**
             * The various textures for each actor and entity
             */
            enum class ID
            {
                Player, /** The player texture */
                Box, /** The box texture */
                Platform, /** The platform texture */
                Wall, /** The box texture */
                Background, /** The background texture */
                Title_Screen, /** The title screen */
                Button, /** The button texture */
            };
        }

        /**
         * The various shaders that can be displayed on the game
         */
        namespace Shaders
        {
            enum class ID
            {
                Brightness_Pass, /** The Brightness levels */
                Down_Sample_Pass, /** The samples downscaling */
                Gaussian_Blur_Pass, /** The Blur effect */
                /* Add_Pass, */
            };
        }

        /**
         * The various fonts displayed throughout the game
         */
        namespace Fonts
        {
            enum class ID
            {
                Connection_II, /** Minecraft-like font */
                Kodomo_Rounded, /** Kiddie Japanese font */
                Free_Font, /** GNU Free font */
                Rampart_One, /** Bubbly font */
            };
        }

        /**
         * The various sound effects that can be heard throughout the usage of the software
         */
        namespace Sound_Effect
        {
            enum class ID
            {
                Player_Footsteps_Outdoor_Boots,
                Player_Footsteps_Outdoor_Boots_On_Wood,
                Player_Footsteps_Shoes_Fast_01,
                Player_Footsteps_Shoes_On_Wood_01,
                Player_Footsteps_Shoes_On_Wood_02,
                Player_Footsteps_Snow_01,
                Player_Footsteps_Snow_02,
                Player_Footsteps_Soft_Fast,
                Player_Footsteps_Stair_Ascent_Creaky,
                Player_Footsteps_Water_01,
                Player_Footsteps_Water_02,
                Box_Movement,
                Level_Complete,
                Game_Complete,
                Button_Beep_01,
                Button_Beep_02,
                Button_Click_01,
                Button_Click_02,
                Button_Click_03,
                Button_Pop_01,
                Button_Pop_02,
                Button_Switch_01,
                Button_Switch_02,
            };
        }

        /**
         * The various songs that can be played throughout the game
         */
        namespace Music
        {
            enum class ID
            {
                Field_Desolate_Domain,
                Field_Golden_Harvest,
                Field_Greatest_Nation,
                Field_Hades_Holiday,
                Field_Homeland_Return,
                Field_Shattered_Land,
                Theme_Courting_The_Princess,
                Theme_Festival_Fun,
                Theme_Funeral_March,
                Theme_Tournament_Time,
                Town_Childhood_Home,
                Town_Fancy_Castle,
                Town_Little_Village,
                Town_Nice_Day_Out,
                Town_Old_Palace,
                Town_Peaceful_Place,
                Town_Pleasant_peasants,
                Town_Shop_Hopping,
                Town_Spooky_Manor,
                Town_Tavern_Tune,
            };
        }
    }

    template< typename Resource, typename Identifier >
    class Resource_Holder;

    using Texture_Holder = Resource_Holder< sf::Texture, gui::Textures::ID >; /** The texture holder */
    using Font_Holder = Resource_Holder< sf::Font, gui::Fonts::ID >; /** The font holder */
    using Shader_Holder = Resource_Holder< sf::Shader, gui::Shaders::ID >; /** The shader holder */
    using Sound_Buffer_Holder = Resource_Holder< sf::SoundBuffer, gui::Sound_Effect::ID >; /** The sound effects holder */
}


#endif //SOKOBAN_RESOURCE_IDENTIFIERS_HPP
