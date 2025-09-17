#include "gui/Music_Player.hpp"
#include "gui/Resource_Bundle.hpp"
#include "gui/Resource_Identifiers.hpp"
#include "gui/Sound_Player.hpp"
#include "input/Keyboard.hpp"
#include "input/Mouse.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <gui/states/State.hpp>

#include <gui/states/State_Stack.hpp>
#include <memory>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the context
 * @param window The window where the entities and components have to be displayed on
 * @param textures The various textures that characterize each entity and component
 * @param fonts The various fonts used throughout the usage of the software
 * @param music The various songs that can be heard
 * @param sounds The various sound effects played
 * @param resource_bundle The various strings to load based on the detected language
 * @param keyboard The default keyboard input handler
 * @param mouse The default mouse input handler
 */
State::Context::Context( const sf::RenderWindow& window, const Texture_Holder& textures, const Font_Holder& fonts, const Music_Player& music,
                         const Sound_Player& sounds, const Resource_Bundle& resource_bundle, const input::Keyboard& keyboard, const input::Mouse& mouse )
    : _window( nullptr )
      , _textures( nullptr )
      , _fonts( nullptr )
      , _music( nullptr )
      , _sounds( nullptr )
      , _resource_bundle( nullptr )
      , _keyboard( nullptr )
      , _mouse( nullptr )
{
    _window = std::make_shared<sf::RenderWindow>( window );
    _textures = std::make_shared<Texture_Holder>( textures );
    _fonts = std::make_shared<Font_Holder>( fonts );
    _music = std::make_shared<Music_Player>( music );
    _sounds = std::make_shared<Sound_Player>( sounds );
    _resource_bundle = std::make_shared<Resource_Bundle>( resource_bundle );
    _keyboard = std::make_shared<input::Keyboard>( keyboard );
    _mouse = std::make_shared<input::Mouse>( mouse );
}

/**
 * Default constructor for a state
 * @param stack The stack containing the state
 * @param context The context that can be accessed throughout each state
 */
State::State( State_Stack& stack, const Context& context )
    : _stack( &stack )
      , _context( context )
{
}

/**
 * Default state destructor
 */
State::~State()
= default;

/**
 * Function meant to insert a state inside the stack based on its ID
 * @param stateID The unique ID of the state
 */
void State::request_stack_push( const States::ID& stateID ) const
{
    _stack->push_state( stateID );
}

/**
 * Function meant to remove a state from the stack
 */
void State::request_stack_pop() const
{
    _stack->pop_state();
}

/**
 * Stack meant to clear out completely the stack
 */
void State::request_state_clear() const
{
    _stack->clear_states();
}

/**
 * Getter for the context accessed all around the states
 * @return The context to which we can access the various resources
 */
State::Context State::get_context() const
{
    return _context;
}
