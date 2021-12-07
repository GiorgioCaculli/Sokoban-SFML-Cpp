#include "State_Game.hpp"

#include "../../../util/Logger.hpp"

#include "../Music_Player.hpp"
#include "../Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <boost/filesystem.hpp>

using namespace sokoban::ui::gui;
using namespace sokoban::util;


namespace
{
    int current_level;
    int reset_counter = 0;
}

/**
 * Alphabetical sorting algorithm for the various paths found
 * @param a A first path to sort
 * @param b A second path to sort with
 * @return The paths in the right order
 */
bool sort_alphabetically( const boost::filesystem::path &a, const boost::filesystem::path &b )
{
    return a.string() < b.string();
}

/**
 * Getter for the various levels that have been detected inside the folder
 */
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

/**
 * Default constructor for the Game State
 * @param stack The stack containing the various states
 * @param context The context containing the various resources
 */
State_Game::State_Game( State_Stack &stack, Context context )
        : State( stack, context )
        , _window( *context._window )
          , _level()
          , _levels()
          , _text()
{
    _window.setKeyRepeatEnabled( true );
    context._music->play( Music::Town_Peaceful_Place );
    _text.setFont( context._fonts->get( Fonts::Connection_II ) );
    _text.setFillColor( sf::Color::Black );
    Logger::log( LoggerLevel::INFO, "Init levels" );
    _levels = std::vector< std::string >();

    if ( get_all_levels().empty() )
    {
        Logger::log( LoggerLevel::INFO, "No levels loaded" );
        return;
    }

    for ( const boost::filesystem::path &path: get_all_levels() )
    {
        _levels.emplace_back( path.string() );
    }

    Logger::log( LoggerLevel::INFO, "Levels loaded" );
    for ( const std::string &lvl: _levels )
    {
        Logger::log( LoggerLevel::INFO, lvl );
    }
    current_level = 0;
    _text.setFont( context._fonts->get( Fonts::Connection_II ) );
    _level = _levels.at( current_level );
    Logger::log( LoggerLevel::DEBUG, "Level loaded: " + _level );
    _world = new World( *context._window, model::Board( _level ), *context._fonts, *context._sounds );
}

/**
 * Default destructor for the Game state
 */
State_Game::~State_Game()
{
    delete _world;
}

/**
 * Realtime update of the visually available Game window
 * @param dt The clock time
 * @return always true
 */
bool State_Game::update( sf::Time dt )
{
    _world->update( dt );
    return true;
}

/**
 * Function to draw the visual components of the Game state
 */
void State_Game::draw()
{
    _world->draw();
    if ( _world->is_board_completed() )
    {
        if ( _levels.size() <= current_level )
        {
            _text.setCharacterSize( 50 );
            Utility::center_origin( _text );
            _text.setString( L"All Levels Completed!" );
            _text.setPosition( get_context()._window->getView().getSize() / 2.f );
            get_context()._window->draw( _text );
        }
        else
        {
            _text.setCharacterSize( 50 );
            Utility::center_origin( _text );
            _text.setString( L"Level Completed\nPress ENTER to continue!" );
            _text.setPosition( get_context()._window->getView().getSize() / 2.f );
            get_context()._window->draw( _text );
        }
    }
}

/**
 * Event handler meant for each interaction possible within the Game state
 * @param event The event executed
 * @return always true
 */
bool State_Game::handle_event( const sf::Event &event )
{
    if( event.type == sf::Event::KeyPressed )
    {
        if( _world->is_board_completed() )
        {
            if ( event.key.code == sf::Keyboard::Enter )
            {
                next_level();
            }
        }
        else
        {
            if( event.key.code == sf::Keyboard::Escape )
            {
                request_stack_push( States::Pause );
            }
            else if( event.key.code == sf::Keyboard::R )
            {
                reset_board();
            }
            else if( event.key.code == sf::Keyboard::S )
            {
                next_level();
            }
            else if( event.key.code == sf::Keyboard::X )
            {
                prev_level();
            }
            if( event.key.code == sf::Keyboard::Up )
            {
                _world->move_up( true );
            }
            else if( event.key.code == sf::Keyboard::Down )
            {
                _world->move_down( true );
            }
            else if( event.key.code == sf::Keyboard::Left )
            {
                _world->move_left( true );
            }
            else if( event.key.code == sf::Keyboard::Right )
            {
                _world->move_right( true );
            }
        }
    }
    else if( event.type == sf::Event::KeyReleased )
    {
        if( _world->is_board_completed() )
        {
        }
        else
        {
            if( event.key.code == sf::Keyboard::Up )
            {
                _world->move_up( false );
            }
            else if( event.key.code == sf::Keyboard::Down )
            {
                _world->move_down( false );
            }
            else if( event.key.code == sf::Keyboard::Left )
            {
                _world->move_left( false );
            }
            else if( event.key.code == sf::Keyboard::Right )
            {
                _world->move_right( false );
            }
        }
    }
    return true;
}

/**
 * Board resetting function meant to restart a game board
 */
void State_Game::reset_board()
{
    delete _world;
    _world = new World( _window, model::Board( _level ), *get_context()._fonts, *get_context()._sounds );
    reset_counter++;
    _world->set_reset_counter( reset_counter );
}

/**
 * Function meant to move onto the next level
 */
void State_Game::next_level()
{
    current_level += 1;
    if ( _levels.size() <= current_level )
    {
        current_level = _levels.size() - 1;
        return;
    }
    _level = _levels.at( current_level );
    delete _world;
    _world = new World( _window, model::Board( _level ), *get_context()._fonts, *get_context()._sounds );
    reset_counter = 0;
    _world->set_reset_counter( reset_counter );
}

/**
 * Function meant to return to a previous level
 */
void State_Game::prev_level()
{
    current_level -= 1;
    if ( current_level <= 0 )
    {
        current_level = 1;
        return;
    }
    _level = _levels.at( current_level );
    delete _world;
    _world = new World( _window, model::Board( _level ), *get_context()._fonts, *get_context()._sounds );
    reset_counter = 0;
    _world->set_reset_counter( reset_counter );
}
