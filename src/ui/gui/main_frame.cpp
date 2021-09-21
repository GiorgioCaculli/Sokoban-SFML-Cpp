#include "main_frame.hpp"

#include <iostream>

using namespace sokoban::ui::gui;

const sf::Time MainFrame::time_per_frame = sf::seconds( 1.f / 60.f );
const float MainFrame::player_speed = 100.f;

MainFrame::MainFrame( unsigned short width, unsigned short height )
{
    logger = new Logger( "Main frame" );
    logger->log( LoggerLevel::INFO, "Init Window" );

    player_is_moving_up = false;
    player_is_moving_down = false;
    player_is_moving_left = false;
    player_is_moving_right = false;

    window = new sf::RenderWindow( sf::VideoMode( width, height ), "Sokoban" );
    window->requestFocus();

    /*
    player = new sf::Sprite();
    player_texture = new sf::Texture();

    player_texture->loadFromFile( "assets/images/PNG/Character4.png" );
    player->setTexture( *player_texture );
    player->setPosition( 100.f, 100.f );
     */
}

MainFrame::MainFrame()
        :MainFrame( 1024, 768 )
{

}

MainFrame::~MainFrame()
= default;

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

void MainFrame::process_events()
{
    sf::Event event {};
    while ( window->pollEvent( event ) )
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
            window->close();
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
    sf::Vector2f movement( 0.f, 0.f );

    if ( player_is_moving_up )
    {
        movement.y -= player_speed;
    }
    if ( player_is_moving_down )
    {
        movement.y += player_speed;
    }
    if ( player_is_moving_left )
    {
        movement.x -= player_speed;
    }
    if ( player_is_moving_right )
    {
        movement.x += player_speed;
    }

    player->move( movement * delta_time.asSeconds() );
}

void MainFrame::render()
{
    window->clear();
    window->draw( *player );
    window->display();
}

void MainFrame::set_width( unsigned short width )
{
    this->_width = width;
}

unsigned short MainFrame::get_width() const
{
    return _width;
}

void MainFrame::set_height( unsigned short height )
{
    this->_height = height;
}

unsigned short MainFrame::get_height() const
{
    return _height;
}

unsigned short MainFrame::run()
{
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while ( window->isOpen() )
    {
        sf::Time elapsed_time = clock.restart();
        time_since_last_update += elapsed_time;
        while ( time_since_last_update > time_per_frame )
        {
            time_since_last_update -= time_per_frame;
            process_events();
            update( time_per_frame );
        }
        render();
    }
    return 0;
}
