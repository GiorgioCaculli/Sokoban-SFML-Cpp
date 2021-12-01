#include "Application.hpp"
#include "../../util/Logger.hpp"
#include "states/State.hpp"
#include "states/State_Identifiers.hpp"
#include "states/State_Title.hpp"
#include "states/State_Game.hpp"
#include "states/State_Menu.hpp"
#include "states/State_Pause.hpp"

#include <boost/filesystem.hpp>

#include <iostream>
#include <algorithm>

// TODO: REMOVE AND CORRECT
#include <SFML/Window/Event.hpp>

using namespace sokoban::ui::gui;
using namespace sokoban::util;

const sf::Time Application::_time_per_frame = sf::seconds( 1.f / 10.f );
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

State_Game *_game = nullptr;

Application::Application()
        : _textures()
          , _fonts()
          , _statistics_text()
          , _statistics_update_time()
          , _statistics_num_frames( 0 )
          , _window( sf::VideoMode( WIDTH, HEIGHT, BITS_PER_PIXEL ), "Sokoban", sf::Style::Fullscreen )
{
    _fonts.load( Fonts::Main, "assets/fonts/ConnectionIi-2wj8.otf" );
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

    Logger::log( LoggerLevel::INFO, "Initializing game..." );
    _game = new State_Game( _window, levels, 0 );
}

Application::~Application()
{
    delete _game;
}

void Application::update_statistics( sf::Time elapsed_time )
{
    _statistics_update_time += elapsed_time;
    _statistics_num_frames += 1;
    if ( _statistics_update_time >= sf::seconds( 1.0f ) )
    {
        _statistics_text.setString(
                "Frames / Second = " + std::to_string( _statistics_num_frames ) + "\n" +
                        "Time / Update = " + std::to_string( _statistics_update_time.asMicroseconds() / _statistics_num_frames ) + "us"
        );
        _statistics_update_time -= sf::seconds( 1.0f );
        _statistics_num_frames = 0;
    }
}

void Application::process_input()
{
    sf::Event event {};

    while ( _window.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
        {
            _window.close();
        }
    }

}

void Application::update( const sf::Time &delta_time )
{
    _game->update( delta_time );
}

void Application::render()
{
    _window.clear();
    _game->draw();
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
        sf::Time elapsed_time = clock.restart();
        time_since_last_update += elapsed_time;
        while ( time_since_last_update > _time_per_frame )
        {
            time_since_last_update -= _time_per_frame;
            _game->process_events();
            update( _time_per_frame );
        }
        update_statistics( elapsed_time );
        render();
    }
    return 0;
}

void Application::register_states()
{

}
