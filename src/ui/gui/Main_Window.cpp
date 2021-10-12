#include "Main_Window.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "../../util/Logger.hpp"

using namespace sokoban::ui::gui;
using namespace sokoban::util;

const sf::Time MainFrame::time_per_frame = sf::seconds( 1.f / 60.f );
const int WIDTH = 1440;
const int HEIGHT = WIDTH / 16 * 10;
sf::Music *music;

MainFrame::MainFrame()
        : window( sf::VideoMode( WIDTH, HEIGHT ), "Sokoban", sf::Style::Titlebar | sf::Style::Close )
          , font()
          , statistics_text()
          , statistics_update_time()
          , statistics_num_frames( 0 )
{
    Logger::log( LoggerLevel::INFO, "Init Window" );

    player_is_moving_up = false;
    player_is_moving_down = false;
    player_is_moving_left = false;
    player_is_moving_right = false;

    Logger::log( LoggerLevel::INFO, "Initializing game..." );
    music = new sf::Music();
    music->openFromFile( "assets/music/Town_-_Tavern_Tune.ogg" );
    music->play();
    music->setVolume( 10 );
    music->setLoop( true );
    game = new GameSceneNode( window );
}

MainFrame::~MainFrame()
{
    delete game;
    delete music;
}

void MainFrame::handle_player_input( sf::Keyboard::Key key, bool is_pressed )
{
    if ( key == sf::Keyboard::Z )
    {
        player_is_moving_up = is_pressed;
    }
    else if ( key == sf::Keyboard::S )
    {
        player_is_moving_down = is_pressed;
    }
    else if ( key == sf::Keyboard::Q )
    {
        player_is_moving_left = is_pressed;
    }
    else if ( key == sf::Keyboard::D )
    {
        player_is_moving_right = is_pressed;
    }
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

void MainFrame::process_events()
{
    sf::Event event {};
    while ( window.pollEvent( event ) )
    {
        switch ( event.type )
        {
        case sf::Event::KeyPressed:
            handle_player_input( event.key.code, true );
            break;
        case sf::Event::KeyReleased:
            handle_player_input( event.key.code, false );
            break;
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::Resized:
            break;
        case sf::Event::LostFocus:
            break;
        case sf::Event::GainedFocus:
            break;
        case sf::Event::TextEntered:
            break;
        case sf::Event::MouseWheelMoved:
            break;
        case sf::Event::MouseWheelScrolled:
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::MouseEntered:
            break;
        case sf::Event::MouseLeft:
            break;
        case sf::Event::JoystickButtonPressed:
            break;
        case sf::Event::JoystickButtonReleased:
            break;
        case sf::Event::JoystickMoved:
            break;
        case sf::Event::JoystickConnected:
            break;
        case sf::Event::JoystickDisconnected:
            break;
        case sf::Event::TouchBegan:
            break;
        case sf::Event::TouchMoved:
            break;
        case sf::Event::TouchEnded:
            break;
        case sf::Event::SensorChanged:
            break;
        case sf::Event::Count:
            break;
        }
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
            process_events();
            update( time_per_frame );
        }
        update_statistics( elapsed_time );
        render();
    }
    return 0;
}
