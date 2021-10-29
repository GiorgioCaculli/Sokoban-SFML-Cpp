#ifndef SOKOBAN_EVENT_MANAGER_HPP
#define SOKOBAN_EVENT_MANAGER_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include <unordered_map>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            enum class Event_Type
            {
                Key_Down = sf::Event::KeyPressed,
                Key_Up = sf::Event::KeyReleased,
                Mouse_Button_Down = sf::Event::MouseButtonPressed,
                Mouse_Button_Up = sf::Event::MouseButtonReleased,
                Mouse_Wheel = sf::Event::MouseWheelMoved,
                Window_Resized = sf::Event::Resized,
                Gained_Focus = sf::Event::GainedFocus,
                Lost_Focus = sf::Event::LostFocus,
                Mouse_Entered = sf::Event::MouseEntered,
                Mouse_Left = sf::Event::MouseLeft,
                Closed = sf::Event::Closed,
                Text_Entered = sf::Event::TextEntered,
                Keyboard = sf::Event::Count + 1,
                Mouse,
                Joystick
            };

            struct Event_Info
            {
                Event_Info();
                Event_Info( int event );
                union
                {
                    int code;
                };
            };

            struct Event_Details
            {
                Event_Details( const std::string &bind_name );
                std::string name;
                sf::Vector2i size;
                sf::Uint32 text_entered;
                sf::Vector2i mouse;
                int mouse_wheel_delta;
                int key_code;
                void clear();
            };

            using Events = std::vector< std::pair< Event_Type, Event_Info > >;

            struct Binding
            {
                Binding( const std::string &name );
                ~Binding();
                void bind_event( Event_Type type, Event_Info info = Event_Info() );
                Events events;
                std::string name;
                int c;
                Event_Details details;
            };

            using Bindings = std::unordered_map< std::string, Binding * >;
            using Callback_Container = std::unordered_map< std::string, std::function< void( Event_Details * ) > >;
            enum class State_Type;
            using Callbacks = std::unordered_map< State_Type, Callback_Container >;

            class Event_Manager
            {
            public:
                Event_Manager();
                ~Event_Manager();
                bool add_binding( Binding *binding );
                bool remove_binding( std::string name );
                void set_current_state( State_Type state );
                void set_focus( const bool &focus );
                template< class T >
                    bool add_callback( State_Type state, const std::string name, void( T::*func)( Event_Details * ), T *instance )
                    {
                        auto itr = _callbacks.find( state );
                        auto temp = std::bind( func, instance, std::placeholders::_1 );
                        return itr->second.emplace( name, temp ).second;
                    }
                bool remove_callback( State_Type state, const std::string &name )
                {
                    auto itr = _callbacks.find( state );
                    if ( itr == _callbacks.end() )
                    {
                        return false;
                    }
                    auto itr2 = itr->second.find( name );
                    if ( itr2 == itr->second.end() )
                    {
                        return false;
                    }
                    itr->second.erase( name );
                    return true;
                }
                void handle_event( sf::Event &event );
                void update();
                sf::Vector2i get_mouse_pos( sf::RenderWindow *wind = nullptr );
            private:
                void load_bindings();
                State_Type _current_state;
                Bindings _bindings;
                Callbacks _callbacks;
                bool _has_focus;
            };
        }
    }
}

#endif //SOKOBAN_EVENT_MANAGER_HPP
