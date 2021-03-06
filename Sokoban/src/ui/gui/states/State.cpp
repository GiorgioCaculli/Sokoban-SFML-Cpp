#include <gzc/games/sokoban/ui/gui/sfml/states/State.hpp>

#include <gzc/games/sokoban/ui/gui/sfml/states/State_Stack.hpp>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the context
 * @param window The window where the entities and components have to be displayed on
 * @param textures The various textures that characterize each entity and component
 * @param fonts The various fonts used throughout the usage of the software
 * @param music The various songs that can be heard
 * @param sounds The various sound effects played
 */
State::Context::Context( sf::RenderWindow &window, Texture_Holder &textures, Font_Holder &fonts, Music_Player &music, Sound_Player &sounds )
        : _window( &window )
          , _textures( &textures )
          , _fonts( &fonts )
          , _music( &music )
          , _sounds( &sounds )
{
}

/**
 * Default constructor for a state
 * @param stack The stack containing the state
 * @param context The context that can be accessed throughout each state
 */
State::State( State_Stack &stack, State::Context context )
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
void State::request_stack_push( States::ID stateID )
{
    _stack->push_state( stateID );
}

/**
 * Function meant to remove a state from the stack
 */
void State::request_stack_pop()
{
    _stack->pop_state();
}

/**
 * Stack meant to clear out completely the stack
 */
void State::request_state_clear()
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
