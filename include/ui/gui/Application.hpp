#ifndef SOKOBAN_APPLICATION_HPP
#define SOKOBAN_APPLICATION_HPP

#include <gzc/util/logger/Logger.hpp>
#include <ui/Resource_Holder.hpp>
#include <ui/gui/Resource_Identifiers.hpp>
#include <ui/gui/entities/Entity_Player.hpp>
#include <ui/gui/states/State_Stack.hpp>
#include <ui/gui/Music_Player.hpp>
#include <ui/gui/Sound_Player.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <ui/gui/ResourceBundle.hpp>


namespace sokoban::ui::gui
{
    using namespace gzc::util::logger;

    class Application
            : sf::NonCopyable
    {
    public:
        Application( uint16_t width, uint16_t height, std::string  title = "Sokoban");
        Application();
        Application( const Application& application ) = delete;
        Application &operator=( const Application& application ) = delete;
        ~Application();

        unsigned short run();

    private:
        const uint16_t _width;
        const uint16_t _height;
        std::string _title;
        const uint16_t _bits_per_pixel;
        Logger _logger;
        Resource_Bundle _resource_bundle;
        static const sf::Time _time_per_frame; /** The amount of frames per second we wish to display */
        sf::RenderWindow _window; /** The window where the drawables are shown */
        sf::Font _default_font;
        sf::Text _statistics_text; /** Text with the FPS amount */
        sf::Time _statistics_update_time; /** Timer to update the various statistics */
        std::size_t _statistics_num_frames; /** Number of frames per second globally */
        Music_Player _music; /** The default music player */
        Sound_Player _sounds; /** The default sound player */
        State_Stack _state_stack; /** The stack containing the various states */
        Texture_Holder _textures; /** The default texture holder */
        Font_Holder _fonts; /** The default font holder */
        void process_input();
        void update( const sf::Time& delta_time );
        void render();
        void update_statistics( sf::Time dt );
        void register_states();
    };
}


#endif //SOKOBAN_APPLICATION_HPP
