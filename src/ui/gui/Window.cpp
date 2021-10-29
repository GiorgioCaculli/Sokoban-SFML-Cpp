#include "Window.hpp"

#include <iostream>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

const sf::Time MainFrame::_time_per_frame = sf::seconds( 1.f / 10.f );
const int WIDTH = 1440;
const int HEIGHT = WIDTH / 16 * 10;

MainFrame::MainFrame()
        : _font()
          , _statistics_text()
          , _statistics_update_time()
          , _statistics_num_frames( 0 )
          , _window( sf::VideoMode( WIDTH, HEIGHT ), "Sokoban", sf::Style::Titlebar | sf::Style::Close )
{
    Logger::log( LoggerLevel::INFO, "Init Window" );

    Logger::log( LoggerLevel::INFO, "Initializing _game..." );
    _game = new State_Game( _window, "assets/levels/tutorial.lvl" );
}

MainFrame::~MainFrame()
{
    delete _game;
}

void MainFrame::update_statistics( sf::Time elapsed_time )
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

void MainFrame::update( const sf::Time &delta_time )
{
    _game->update( delta_time );
}

void MainFrame::render()
{
    _window.clear();
    _game->draw();
    _window.setView( _window.getDefaultView() );
    _window.draw( _statistics_text );
    _window.display();
}

unsigned short MainFrame::run()
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
            /* _game->process_events(); */
            update( _time_per_frame );
        }
        _game->process_events();
        update_statistics( elapsed_time );
        render();
    }
    return 0;
}
