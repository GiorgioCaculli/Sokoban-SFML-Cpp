#include "Application.hpp"
#include <util/logger/Logger.hpp>
#include "Utility.hpp"
#include "states/State.hpp"
#include "states/State_Identifiers.hpp"
#include "states/State_Title.hpp"
#include "states/State_Game.hpp"
#include "states/State_Menu.hpp"
#include "states/State_Pause.hpp"
#include "states/State_Settings.hpp"


using namespace sokoban::ui::gui;
using namespace util;

const sf::Time Application::_time_per_frame = sf::seconds( 1.f / 10.f );

namespace
{
    const int WIDTH = 1920;
    const int HEIGHT = WIDTH / 16 * 9;
    const int BITS_PER_PIXEL = 32;
    Logger logger( "Application", "sokoban.log", true );
}

/**
 * Default constructor for the application
 */
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
    logger.log( Logger::Level::DEBUG, "Setting KeyRepeatedEnabled = false" );
    _window.setKeyRepeatEnabled( false );

    logger.log( Logger::Level::DEBUG, "Setting VerticalSyncEnabled = true" );
    _window.setVerticalSyncEnabled( true );

    logger.log( Logger::Level::DEBUG, "Loading fonts" );
    _fonts.load( Fonts::Kodomo_Rounded, "assets/fonts/KodomoRounded.otf" );
    _fonts.load( Fonts::Connection_II, "assets/fonts/ConnectionIi-2wj8.otf" );
    _fonts.load( Fonts::Free_Font, "assets/fonts/freefont/FreeSansBold.ttf" );
    _fonts.load( Fonts::Rampart_One, "assets/fonts/RampartOne-Regular.ttf" );

    logger.log( Logger::Level::DEBUG, "Loading Title Screen Texture" );
    _textures.load( Textures::Title_Screen, "assets/images/Sample_Sokoban.png" );
    _textures.load( Textures::Button, "assets/images/Buttons.png" );

    logger.log( Logger::Level::DEBUG, "Initializing stastistics text" );
    _statistics_text.setFont( _fonts.get( Fonts::Connection_II ) );
    _statistics_text.setPosition( WIDTH / 2.5f, 5.f );
    _statistics_text.setCharacterSize( 10u );
    _statistics_text.setFillColor( sf::Color::Yellow );

    logger.log( Logger::Level::DEBUG, "Registering States" );
    register_states();

    logger.log( Logger::Level::DEBUG, "Setting Title as first State to load" );
    _state_stack.push_state( States::Title );

    logger.log( Logger::Level::DEBUG, "Playing Default Song" );
    _music.play( Music::Town_Pleasant_peasants );
}

/**
 * Application's destructor
 */
Application::~Application()
= default;

/**
 * Realtime update FPS counter
 * @param dt The clock time
 */
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

/**
 * Globalized Event handler per state within stack
 */
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

/**
 * Realtime update all states within stack
 * @param delta_time The clock time
 */
void Application::update( const sf::Time &delta_time )
{
    _state_stack.update( delta_time );
}

/**
 * Visually display everything that makes up the game
 */
void Application::render()
{
    _window.clear();
    _state_stack.draw();
    _window.setView( _window.getDefaultView() );
    _window.draw( _statistics_text );
    _window.display();
}

/**
 * Execute the program and return the execution code
 * @return 0 if run correctly, -1 if not
 */
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

/**
 * Register the various states within the app
 */
void Application::register_states()
{
    logger.log( Logger::Level::DEBUG, "Registering Title State" );
    _state_stack.register_state< State_Title >( States::Title );

    logger.log( Logger::Level::DEBUG, "Registering Menu State" );
    _state_stack.register_state< State_Menu >( States::Menu );

    logger.log( Logger::Level::DEBUG, "Registering Game State" );
    _state_stack.register_state< State_Game >( States::Game );

    logger.log( Logger::Level::DEBUG, "Registering Settings State" );
    _state_stack.register_state< State_Settings >( States::Settings );

    logger.log( Logger::Level::DEBUG, "Registering Pause State" );
    _state_stack.register_state< State_Pause >( States::Pause );
}
