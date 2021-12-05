#include "Application.hpp"
#include "../../util/Logger.hpp"
#include "Utility.hpp"
#include "states/State.hpp"
#include "states/State_Identifiers.hpp"
#include "states/State_Title.hpp"
#include "states/State_Game.hpp"
#include "states/State_Menu.hpp"
#include "states/State_Pause.hpp"
#include "states/State_Settings.hpp"
#include "states/State_Game_Over.hpp"


using namespace sokoban::ui::gui;
using namespace sokoban::util;

const sf::Time Application::_time_per_frame = sf::seconds( 1.f / 10.f );

namespace
{
    const int WIDTH = 1920;
    const int HEIGHT = WIDTH / 16 * 9;
    const int BITS_PER_PIXEL = 32;
}

Application::Application()
        : _window( sf::VideoMode( WIDTH, HEIGHT, BITS_PER_PIXEL ), "Sokoban", sf::Style::Fullscreen )
          , _textures()
          , _fonts()
          , _music()
          , _sounds()
          , _state_stack( State::Context( _window, _textures, _fonts, _music, _sounds ) )
          , _statistics_text()
          , _statistics_update_time()
          , _statistics_num_frames( 0 )
{
    Logger::log( LoggerLevel::DEBUG, "Setting KeyRepeatedEnabled = false" );
    _window.setKeyRepeatEnabled( false );

    Logger::log( LoggerLevel::DEBUG, "Setting VerticalSyncEnabled = true" );
    _window.setVerticalSyncEnabled( true );

    Logger::log( LoggerLevel::DEBUG, "Loading fonts" );
    _fonts.load( Fonts::Kodomo_Rounded, "assets/fonts/KodomoRounded.otf" );
    _fonts.load( Fonts::Connection_II, "assets/fonts/ConnectionIi-2wj8.otf" );
    _fonts.load( Fonts::Free_Font, "assets/fonts/freefont/FreeSansBold.ttf" );
    _fonts.load( Fonts::Rampart_One, "assets/fonts/RampartOne-Regular.ttf" );

    Logger::log( LoggerLevel::DEBUG, "Loading Title Screen Texture" );
    _textures.load( Textures::Title_Screen, "assets/images/Sample_Sokoban.png" );
    _textures.load( Textures::Button, "assets/images/Buttons.png" );

    Logger::log( LoggerLevel::DEBUG, "Initializing stastistics text" );
    _statistics_text.setFont( _fonts.get( Fonts::Connection_II ) );
    _statistics_text.setPosition( WIDTH / 2.5f, 5.f );
    _statistics_text.setCharacterSize( 10u );
    _statistics_text.setFillColor( sf::Color::Yellow );

    Logger::log( LoggerLevel::DEBUG, "Registering States" );
    register_states();

    Logger::log( LoggerLevel::DEBUG, "Setting Title as first State to load" );
    _state_stack.push_state( States::Title );

    Logger::log( LoggerLevel::DEBUG, "Setting default music volume" );
    _music.set_volume( 25.f );

    Logger::log( LoggerLevel::DEBUG, "Playing Default Song" );
    _music.play( Music::Town_Pleasant_peasants );
}

Application::~Application()
= default;

void Application::update_statistics( sf::Time dt )
{
    _statistics_update_time += dt;
    _statistics_num_frames += 1;
    if ( _statistics_update_time >= sf::seconds( 1.0f ) )
    {
        _statistics_text.setString(
                "FPS: " + std::to_string( _statistics_num_frames )
        );
        _statistics_update_time -= sf::seconds( 1.0f );
        _statistics_num_frames = 0;
    }
}

void Application::process_input()
{
    sf::Event event{};

    while ( _window.pollEvent( event ) )
    {
        _state_stack.handle_event( event );
        if ( event.type == sf::Event::Closed )
        {
            _window.close();
        }
    }

}

void Application::update( const sf::Time &delta_time )
{
    _state_stack.update( delta_time );
}

void Application::render()
{
    _window.clear();
    _state_stack.draw();
    _window.setView( _window.getDefaultView() );
    _window.draw( _statistics_text );
    _window.display();
}

unsigned short Application::run()
{
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while ( _window.isOpen() )
    {
        sf::Time dt = clock.restart();
        time_since_last_update += dt;
        while ( time_since_last_update > _time_per_frame )
        {
            time_since_last_update -= _time_per_frame;
            process_input();
            update( _time_per_frame );
            if( _state_stack.is_empty() )
            {
                _window.close();
            }
        }
        update_statistics( dt );
        render();
    }
    return 0;
}

void Application::register_states()
{
    Logger::log( LoggerLevel::DEBUG, "Registering Title State" );
    _state_stack.register_state< State_Title >( States::Title );

    Logger::log( LoggerLevel::DEBUG, "Registering Menu State" );
    _state_stack.register_state< State_Menu >( States::Menu );

    Logger::log( LoggerLevel::DEBUG, "Registering Game State" );
    _state_stack.register_state< State_Game >( States::Game );

    Logger::log( LoggerLevel::DEBUG, "Registering Settings State" );
    _state_stack.register_state< State_Settings >( States::Settings );

    Logger::log( LoggerLevel::DEBUG, "Registering Pause State" );
    _state_stack.register_state< State_Pause >( States::Pause );
}
