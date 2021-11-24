#include "Event_Manager.hpp"

using namespace sokoban::ui::gui;

Event_Info::Event_Info()
{
    code = 0;
}

Event_Info::Event_Info( int event )
{
    code = event;
}

Event_Details::Event_Details( const std::string &bind_name )
        : name( bind_name )
{
    clear();
}

void Event_Details::clear()
{
    size = sf::Vector2i( 0, 0 );
    text_entered = 0;
    mouse = sf::Vector2i( 0, 0 );
    mouse_wheel_delta = 0;
    key_code = -1;
}

Binding::Binding( const std::string &name )
        : name( name )
          , details( name )
          , c( 0 )
{
}

Binding::~Binding()
= default;

void Binding::bind_event( Event_Type type, Event_Info info )
{
    events.emplace_back( type, info );
}

Event_Manager::Event_Manager()
        : _current_state( State_Type( 0 ) )
          , _has_focus( true )
{
    load_bindings();
}

Event_Manager::~Event_Manager()
{
    for ( auto &itr: _bindings )
    {
        delete itr.second;
    }
}

bool Event_Manager::add_binding( Binding *binding )
{
    if ( _bindings.find( binding->name ) != _bindings.end() )
    {
        return false;
    }

    return _bindings.emplace( binding->name, binding ).second;
}

bool Event_Manager::remove_binding( std::string name )
{
    auto itr = _bindings.find( name );
    if ( itr == _bindings.end() )
    {
        return false;
    }
    delete itr->second;
    _bindings.erase( itr );
    return true;
}

void Event_Manager::set_current_state( State_Type state )
{
    _current_state = state;
}

void Event_Manager::set_focus( const bool &focus )
{
    _has_focus = focus;
}

void Event_Manager::handle_event( sf::Event &event )
{
    for ( auto &binding_itr: _bindings )
    {
        Binding *bind = binding_itr.second;
        for ( auto event_itr: bind->events )
        {
            Event_Type sfml_event = ( Event_Type ) event.type;
            if ( event_itr.first != sfml_event )
            {
                continue;
            }
            if ( sfml_event == Event_Type::Key_Down || sfml_event == Event_Type::Key_Up )
            {
                if ( event_itr.second.code == event.key.code )
                {
                    if ( bind->details.key_code != -1 )
                    {
                        bind->details.key_code = event_itr.second.code;
                    }
                    ++( bind->c );
                    break;
                }
            }
            else if ( sfml_event == Event_Type::Mouse_Button_Down || sfml_event == Event_Type::Mouse_Button_Up )
            {
                if ( event_itr.second.code == event.mouseButton.button )
                {
                    bind->details.mouse.x = event.mouseButton.x;
                    bind->details.mouse.y = event.mouseButton.y;
                    if ( bind->details.key_code != -1 )
                    {
                        bind->details.key_code = event_itr.second.code;
                    }
                }
                ++( bind->c );
                break;
            }
            else
            {
                if ( sfml_event == Event_Type::Mouse_Wheel )
                {
                    bind->details.mouse_wheel_delta = event.mouseWheel.delta;
                }
                else if ( sfml_event == Event_Type::Window_Resized )
                {
                    bind->details.size.x = event.size.width;
                    bind->details.size.y = event.size.height;
                }
                else if ( sfml_event == Event_Type::Text_Entered )
                {
                    bind->details.text_entered = event.text.unicode;
                }
                ++( bind->c );
            }
        }
    }
}

void Event_Manager::update()
{
    if ( !_has_focus )
    {
        return;
    }
    for ( auto &binding_itr: _bindings )
    {
        Binding *bind = binding_itr.second;
        for ( auto &event_itr: bind->events )
        {
            switch ( event_itr.first )
            {
                case Event_Type::Keyboard:
                    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( event_itr.second.code ) ) )
                    {
                        if ( bind->details.key_code != -1 )
                        {
                            bind->details.key_code = event_itr.second.code;
                        }
                        ++( bind->c );
                    }
                    break;
                case Event_Type::Mouse:
                    if ( sf::Mouse::isButtonPressed( sf::Mouse::Button( event_itr.second.code ) ) )
                    {
                        if ( bind->details.key_code != -1 )
                        {
                            bind->details.key_code = event_itr.second.code;
                        }
                        ++( bind->c );
                    }
                    break;
                case Event_Type::Joystick:
                    break;
            }
        }
        if ( bind->events.size() == bind->c )
        {
            auto state_callbacks = _callbacks.find( _current_state );
            auto other_callbacks = _callbacks.find( State_Type( 0 ) );

            if ( state_callbacks != _callbacks.end() )
            {
                auto call_itr = state_callbacks->second.find( bind->name );
                if ( call_itr != state_callbacks->second.end() )
                {
                    call_itr->second( &bind->details );
                }
            }
            if ( other_callbacks != _callbacks.end() )
            {
                auto call_itr = other_callbacks->second.find( bind->name );
                if ( call_itr != other_callbacks->second.end() )
                {
                    call_itr->second( &bind->details );
                }
            }
        }
        bind->c = 0;
        bind->details.clear();
    }
}

sf::Vector2i Event_Manager::get_mouse_pos( sf::RenderWindow *wind )
{
    return ( wind ? sf::Mouse::getPosition( *wind ) : sf::Mouse::getPosition() );
}

void Event_Manager::load_bindings()
{
    std::string delimiter = ":";

    std::ifstream bindings;
    bindings.open( "res/keys.cfg" );
    if ( !bindings.is_open() )
    {
        std::cout << "! Failed loading res/keys.cfg." << std::endl;
        return;
    }
    std::string line;
    while ( std::getline( bindings, line ) )
    {
        std::stringstream key_stream( line );
        std::string callback_name;
        key_stream >> callback_name;
        Binding *bind = new Binding( callback_name );
        while ( !key_stream.eof() )
        {
            std::string key_val;
            key_stream >> key_val;
            if ( key_stream.fail() )
            {
                key_stream.clear();
                break;
            }
            int start = 0;
            int end = key_val.find( delimiter );
            if ( end == std::string::npos )
            {
                delete bind;
                bind = nullptr;
                break;
            }
            Event_Type type = Event_Type( std::stoi( key_val.substr( start, end - start ) ) );
            int code = std::stoi( key_val.substr( end + delimiter.length(),
                    key_val.find( delimiter, end + delimiter.length() ) ) );
            Event_Info event_info;
            event_info.code = code;
            bind->bind_event( type, event_info );
        }
        if ( !add_binding( bind ) )
        {
            delete bind;
        }
        bind = nullptr;
    }
    bindings.close();
}
