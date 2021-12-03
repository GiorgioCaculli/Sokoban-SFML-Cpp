#include "Application.hpp"
#include "../../util/Logger.hpp"
#include "Utility.hpp"
#include "states/State.hpp"
#include "states/State_Identifiers.hpp"
#include "states/State_Title.hpp"
#include "states/State_Game.hpp"
#include "states/State_Menu.hpp"
#include "states/State_Pause.hpp"

#include <boost/filesystem.hpp>

#include <iostream>
#include <algorithm>

using namespace sokoban::ui::gui;
using namespace sokoban::util;

const sf::Time Application::time_per_frame = sf::seconds( 1.f / 10.f );
const int WIDTH = 1920;
const int HEIGHT = WIDTH / 16 * 9;
const int BITS_PER_PIXEL = 32;

bool sort_alphabetically( const boost::filesystem::path &a, const boost::filesystem::path &b )
{
    return a.string() < b.string();
}

std::vector< boost::filesystem::path > get_all_levels()
{
    const boost::filesystem::path root = "assets/levels";
    const std::string extension = ".lvl";
    std::vector< boost::filesystem::path > paths;
    if ( boost::filesystem::exists( root ) && boost::filesystem::is_directory( root ) )
    {
        for ( auto const &entry: boost::filesystem::recursive_directory_iterator( root ) )
        {
            if ( boost::filesystem::is_regular_file( entry ) )
            {
                paths.emplace_back( entry );
            }
        }
    }

    std::sort( paths.begin(), paths.end(), sort_alphabetically );

    return paths;
}

std::vector< std::string > levels = std::vector< std::string >();

Application::Application()
        : _window( sf::VideoMode( WIDTH, HEIGHT, BITS_PER_PIXEL ), "Sokoban", sf::Style::Fullscreen )
          , _textures()
          , _fonts()
          , _state_stack( State::Context( _window, _textures, _fonts ) )
          , _statistics_text()
          , _statistics_update_time()
          , _statistics_num_frames( 0 )
{
    _window.setKeyRepeatEnabled( false );
    _fonts.load( Fonts::KodomoRounded, "assets/fonts/KodomoRounded.otf" );
    _fonts.load( Fonts::ConnectionII, "assets/fonts/ConnectionIi-2wj8.otf" );
    _fonts.load( Fonts::FreeFont, "assets/fonts/freefont/FreeSansBold.ttf" );
    _fonts.load( Fonts::RampartOne, "assets/fonts/RampartOne-Regular.ttf" );
    _fonts.load( Fonts::Main, "assets/fonts/RampartOne-Regular.ttf" );
    _textures.load( Textures::TitleScreen, "assets/images/Sample_Sokoban.png" );
    _statistics_text.setFont( _fonts.get( Fonts::Main ) );
    _statistics_text.setPosition( WIDTH / 2.5f, 5.f );
    _statistics_text.setCharacterSize( 10u );
    _statistics_text.setFillColor( sf::Color::Yellow );

    Logger::log( LoggerLevel::INFO, "Init levels" );

    if ( get_all_levels().empty() )
    {
        std::cout << "No levels loaded" << std::endl;
        _window.close();
        return;
    }

    for ( const boost::filesystem::path &path: get_all_levels() )
    {
        levels.emplace_back( path.string() );
    }

    std::cout << "Levels loaded" << std::endl;
    for ( const std::string &lvl: levels )
    {
        std::cout << lvl << std::endl;
    }

    register_states();
    _state_stack.push_state( States::Title );
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
        while ( time_since_last_update > time_per_frame )
        {
            time_since_last_update -= time_per_frame;
            process_input();
            update( time_per_frame );
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
    _state_stack.register_state< State_Title >( States::Title );
    _state_stack.register_state< State_Menu >( States::Menu );
}
