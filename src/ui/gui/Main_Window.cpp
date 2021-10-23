#include "Main_Window.hpp"

#include <iostream>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

const sf::Time MainFrame::time_per_frame = sf::seconds( 1.f / 10.f );
const int WIDTH = 1440;
const int HEIGHT = WIDTH / 16 * 10;

MainFrame::MainFrame()
          : font()
          , statistics_text()
          , statistics_update_time()
          , statistics_num_frames( 0 )
          , window( sf::VideoMode( WIDTH, HEIGHT ), "Sokoban", sf::Style::Titlebar | sf::Style::Close )
{
    Logger::log( LoggerLevel::INFO, "Init Window" );

    Logger::log( LoggerLevel::INFO, "Initializing game..." );
    game = new GameSceneNode( window );
}

MainFrame::~MainFrame()
{
    delete game;
}

void MainFrame::update_statistics( sf::Time elapsed_time )
{
    statistics_update_time += elapsed_time;
    statistics_num_frames += 1;
    if ( statistics_update_time >= sf::seconds( 1.0f ) )
    {
        statistics_text.setString(
                "Frames / Second = " + std::to_string( statistics_num_frames ) + "\n" +
                        "Time / Update = " + std::to_string( statistics_update_time.asMicroseconds() / statistics_num_frames ) + "us"
        );
        statistics_update_time -= sf::seconds( 1.0f );
        statistics_num_frames = 0;
    }
}

void MainFrame::update( sf::Time delta_time )
{
    game->update( delta_time );
}

void MainFrame::render()
{
    window.clear();
    game->draw();
    window.setView( window.getDefaultView() );
    window.draw( statistics_text );
    window.display();
}

unsigned short MainFrame::run()
{
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while ( window.isOpen() )
    {
        sf::Time elapsed_time = clock.restart();
        time_since_last_update += elapsed_time;
        while ( time_since_last_update > time_per_frame )
        {
            time_since_last_update -= time_per_frame;
            /* game->process_events(); */
            update( time_per_frame );
        }
        game->process_events();
        update_statistics( elapsed_time );
        render();
    }
    return 0;
}
