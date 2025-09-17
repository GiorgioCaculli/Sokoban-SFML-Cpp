#include "gui/Resource_Identifiers.hpp"
#include <boost/filesystem/path.hpp>
#include <gui/states/State_Game.hpp>

#include <gzc/util/logger/Logger.hpp>

#include <gui/Music_Player.hpp>
#include <gui/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <boost/filesystem.hpp>

#include <algorithm>
#include <memory>
#include <vector>

using namespace sokoban::ui::gui;
using namespace gzc::util::logger;


/**
 * Alphabetical sorting algorithm for the various paths found
 * @param a A first path to sort
 * @param b A second path to sort with
 * @return The paths in the right order
 */
bool sort_alphabetically( const boost::filesystem::path& a, const boost::filesystem::path& b )
{
    return a.string() < b.string();
}

/**
 * Getter for the various levels that have been detected inside the folder
 */
std::vector< boost::filesystem::path > get_all_levels()
{
    const boost::filesystem::path root = "res/levels";
    const std::string extension = ".lvl";
    std::vector< boost::filesystem::path > paths;
    if ( boost::filesystem::exists( root ) && boost::filesystem::is_directory( root ) )
    {
        for ( auto const& entry: boost::filesystem::recursive_directory_iterator( root ) )
        {
            if ( boost::filesystem::is_regular_file( entry ) )
            {
                paths.emplace_back( entry );
            }
        }
    }

    std::ranges::sort( paths );

    return paths;
}

/**
 * Default constructor for the Game State
 * @param stack The stack containing the various states
 * @param context The context containing the various resources
 */
State_Game::State_Game( State_Stack& stack, const Context& context )
    : State( stack, context )
      , _window( *context._window )
      , _text( context._fonts->get( Fonts::ID::Connection_II ) )
{
    _window.setKeyRepeatEnabled( true );
    context._music->play( Music::ID::Town_Peaceful_Place );
    _text.setFillColor( sf::Color::Black );
    logger.log( Logger::Level::INFO, "Init levels" );
    _levels = std::vector< std::string >();

    if ( get_all_levels().empty() )
    {
        logger.log( Logger::Level::INFO, "No levels loaded" );
        return;
    }

    for ( const boost::filesystem::path& path: get_all_levels() )
    {
        _levels.emplace_back( path.string() );
    }

    logger.log( Logger::Level::INFO, "Levels loaded" );
    for ( const std::string& lvl: _levels )
    {
        logger.log( Logger::Level::INFO, lvl );
    }
    current_level = 0;
    _text.setFont( context._fonts->get( Fonts::ID::Connection_II ) );
    _level = _levels.at( current_level );
    logger.log( Logger::Level::DEBUG, "Level loaded: " + _level );
    _world = std::make_shared< World >( *context._window, gzc::sokoban::core::Board( _level ), *context._fonts, *context._sounds );
}

/**
 * Default destructor for the Game state
 */
State_Game::~State_Game()
= default;

/**
 * Realtime update of the visually available Game window
 * @param dt The clock time
 * @return always true
 */
bool State_Game::update( const sf::Time dt )
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
        } else
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
bool State_Game::handle_event( const sf::Event& event )
{
    return handle_keyboard_events( event ) || handle_mouse_events( event );
}

/**
 * Board resetting function meant to restart a game board
 */
void State_Game::reset_board()
{
    _world = std::make_shared< World >( _window, gzc::sokoban::core::Board( _level ), *get_context()._fonts, *get_context()._sounds );
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
    _world = std::make_shared< World >( _window, gzc::sokoban::core::Board( _level ), *get_context()._fonts, *get_context()._sounds );
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
    _world = std::make_shared< World >( _window, gzc::sokoban::core::Board( _level ), *get_context()._fonts, *get_context()._sounds );
    reset_counter = 0;
    _world->set_reset_counter( reset_counter );
}

bool State_Game::handle_keyboard_events( const sf::Event& event )
{
    const auto context = get_context();

    context._keyboard->releasing(event, { sf::Keyboard::Scancode::R }, [ this ]
    {
        reset_board();
        return true;
    });

    context._keyboard->releasing(event, { sf::Keyboard::Scancode::S }, [ this ]
    {
        next_level();
        return true;
    });

    context._keyboard->releasing(event, { sf::Keyboard::Scancode::X }, [ this ]
    {
        prev_level();
        return true;
    });

    /* TODO: Rewrite this IF - ELSE chain 'properly' */

    if ( const auto *keyPressed = event.getIf<sf::Event::KeyPressed>() )
    {
        if ( _world->is_board_completed() )
        {
            /* Temporarily no reason for the world to do anything immediate on key pressed */
        } else
        {
            if ( keyPressed->scancode == sf::Keyboard::Scancode::Up )
            {
                _world->move_up( true );
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::Down )
            {
                _world->move_down( true );
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::Left )
            {
                _world->move_left( true );
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::Right )
            {
                _world->move_right( true );
            }
        }
    } else if ( const auto *keyReleased = event.getIf<sf::Event::KeyReleased>() )
    {
        if ( _world->is_board_completed() )
        {
            if ( keyReleased->scancode == sf::Keyboard::Scancode::Enter )
            {
                next_level();
            }
        } else
        {
            if ( keyReleased->scancode == sf::Keyboard::Scancode::Escape )
            {
                request_stack_push( States::ID::Pause );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Up )
            {
                _world->move_up( false );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Down )
            {
                _world->move_down( false );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Left )
            {
                _world->move_left( false );
            } else if ( keyReleased->scancode == sf::Keyboard::Scancode::Right )
            {
                _world->move_right( false );
            }
        }
    }
    return false;
}

bool State_Game::handle_mouse_events( const sf::Event& event )
{
    const auto context = get_context();
    if ( _world->is_board_completed() )
    {
        context._mouse->releasing( event, sf::Mouse::Button::Left, *context._window, [ this ]
        {
            next_level();
            return true;
        } );
    }
    return false;
}
