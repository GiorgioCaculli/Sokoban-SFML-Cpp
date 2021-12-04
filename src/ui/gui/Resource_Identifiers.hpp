#ifndef SOKOBAN_RESOURCE_IDENTIFIERS_HPP
#define SOKOBAN_RESOURCE_IDENTIFIERS_HPP

namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class SoundBuffer;
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
                    Title_Screen,
                    Button,
                };
            }

            namespace Shaders
            {
                enum ID
                {
                    Brightness_Pass,
                    Down_Sample_Pass,
                    Gaussian_Blur_Pass,
                    Add_Pass,
                };
            }

            namespace Fonts
            {
                enum ID
                {
                    Connection_II,
                    Kodomo_Rounded,
                    Free_Font,
                    Rampart_One,
                };
            }

            namespace Sound_Effect
            {
                enum ID
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

            namespace Music
            {
                enum ID
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

        typedef Resource_Holder< sf::Texture, gui::Textures::ID > Texture_Holder;
        typedef Resource_Holder< sf::Font, gui::Fonts::ID > Font_Holder;
        typedef Resource_Holder< sf::Shader, gui::Shaders::ID > Shader_Holder;
        typedef Resource_Holder< sf::SoundBuffer, gui::Sound_Effect::ID > Sound_Buffer_Holder;
    }
}

#endif //SOKOBAN_RESOURCE_IDENTIFIERS_HPP
