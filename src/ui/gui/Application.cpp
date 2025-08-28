#include <ui/gui/Application.hpp>
#include <ui/gui/Utility.hpp>
#include <ui/gui/states/State.hpp>
#include <ui/gui/states/State_Identifiers.hpp>
#include <ui/gui/states/State_Title.hpp>
#include <ui/gui/states/State_Game.hpp>
#include <ui/gui/states/State_Menu.hpp>
#include <ui/gui/states/State_Pause.hpp>
#include <ui/gui/states/State_Settings.hpp>


using namespace sokoban::ui::gui;
using namespace gzc::util::logger;

const sf::Time Application::_time_per_frame = sf::seconds( 1.f / 10.f );

/**
 * Default constructor for the application
 */
Application::Application()
    : _window( sf::VideoMode( sf::Vector2u( _width, _height ), _bits_per_pixel ), "Sokoban", sf::State::Fullscreen )
      , _textures()
      , _fonts()
      , _music()
      , _sounds()
      , _state_stack( State::Context( _window, _textures, _fonts, _music, _sounds ) )
      , _statistics_text()
      , _statistics_update_time()
      , _statistics_num_frames( 0 )
      , _width( 1920 )
      , _height( _width / 16 * 9 )
      , _bits_per_pixel( 32 )
      , _logger( "Application", "sokoban.log", true )
{
    _logger.log( Logger::Level::DEBUG, "Setting KeyRepeatedEnabled = false" );
    _window.setKeyRepeatEnabled( false );

    _logger.log( Logger::Level::DEBUG, "Setting VerticalSyncEnabled = true" );
    _window.setVerticalSyncEnabled( true );

    _logger.log( Logger::Level::DEBUG, "Loading fonts" );
    _fonts.load( Fonts::Kodomo_Rounded, "res/fonts/KodomoRounded.otf" );
    _fonts.load( Fonts::Connection_II, "res/fonts/ConnectionIi-2wj8.otf" );
    _fonts.load( Fonts::Free_Font, "res/fonts/freefont/FreeSansBold.ttf" );
    _fonts.load( Fonts::Rampart_One, "res/fonts/RampartOne-Regular.ttf" );

    _logger.log( Logger::Level::DEBUG, "Loading Title Screen Texture" );
    _textures.load( Textures::Title_Screen, "res/images/Sample_Sokoban.png" );
    _textures.load( Textures::Button, "res/images/Buttons.png" );

    _logger.log( Logger::Level::DEBUG, "Initializing stastistics text" );
    _statistics_text.setFont( _fonts.get( Fonts::Connection_II ) );
    _statistics_text.setPosition( sf::Vector2f( _width / 2.5f, 5.f ) );
    _statistics_text.setCharacterSize( 10u );
    _statistics_text.setFillColor( sf::Color::Yellow );

    _logger.log( Logger::Level::DEBUG, "Registering States" );
    register_states();

    _logger.log( Logger::Level::DEBUG, "Setting Title as first State to load" );
    _state_stack.push_state( States::Title );

    _logger.log( Logger::Level::DEBUG, "Playing Default Song" );
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
void Application::update( const sf::Time& delta_time )
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
            if ( _state_stack.is_empty() )
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
    _logger.log( Logger::Level::DEBUG, "Registering Title State" );
    _state_stack.register_state< State_Title >( States::Title );

    _logger.log( Logger::Level::DEBUG, "Registering Menu State" );
    _state_stack.register_state< State_Menu >( States::Menu );

    _logger.log( Logger::Level::DEBUG, "Registering Game State" );
    _state_stack.register_state< State_Game >( States::Game );

    _logger.log( Logger::Level::DEBUG, "Registering Settings State" );
    _state_stack.register_state< State_Settings >( States::Settings );

    _logger.log( Logger::Level::DEBUG, "Registering Pause State" );
    _state_stack.register_state< State_Pause >( States::Pause );
}
