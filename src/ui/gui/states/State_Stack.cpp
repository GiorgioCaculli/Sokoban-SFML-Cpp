#include <ranges>
#include <ui/gui/states/State_Stack.hpp>

#include <cassert>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the Stack containing the various states
 * @param context Globally accessible context containing the various resources
 */
State_Stack::State_Stack( State::Context context )
    : _stack()
      , _pending_list()
      , _context( context )
      , _factories()
{
}

/**
 * Realtime update the various states within the stack
 * @param dt The clock time
 */
void State_Stack::update( sf::Time dt )
{
    for ( const auto & itr : std::ranges::reverse_view(_stack))
    {
        if ( !itr->update( dt ) )
        {
            break;
        }
    }
    apply_pending_changes();
}

/**
 * Visually display the various states within the stack
 */
void State_Stack::draw()
{
    for ( State::Ptr& state: _stack )
    {
        state->draw();
    }
}

/**
 * Event handler for each state present within the stack
 * @param event The event called
 */
void State_Stack::handle_event( const sf::Event& event )
{
    for ( const auto & itr : std::ranges::reverse_view(_stack))
    {
        if ( !itr->handle_event( event ) )
        {
            break;
        }
    }
    apply_pending_changes();
}

/**
 * The state to push ahead of the stack
 * @param state_id The ID that characterizes the state
 */
void State_Stack::push_state( States::ID state_id )
{
    _pending_list.emplace_back( Push, state_id );
}

/**
 * Function that pops a state from within the stack
 */
void State_Stack::pop_state()
{
    _pending_list.emplace_back( Pop );
}

/**
 * Function that clears out the entirety of the states within the stack
 */
void State_Stack::clear_states()
{
    _pending_list.emplace_back( Clear );
}

/**
 * Verifier that checks whether the stack is empty or not
 * @return Whether the stack is empty or not
 */
bool State_Stack::is_empty() const
{
    return _stack.empty();
}

/**
 * Function that creates a state based on its ID
 * @param state_id The ID that characterizes the state
 * @return The State from its ID
 */
State::Ptr State_Stack::create_state( States::ID state_id )
{
    auto found = _factories.find( state_id );
    assert( found != _factories.end() );
    return found->second();
}

/**
 * Function that handles the various interaction called within the game
 */
void State_Stack::apply_pending_changes()
{
    for ( Pending_Change change: _pending_list )
    {
        switch ( change._action )
        {
            case Push:
                _stack.push_back( create_state( change._state_id ) );
                break;
            case Pop:
                _stack.pop_back();
                break;
            case Clear:
                _stack.clear();
                break;
        }
    }
    _pending_list.clear();
}

/**
 * Default constructor for a possible pending change
 * @param action The action that has to be executed
 * @param state_id The ID that characterizes the state that calls the action
 */
State_Stack::Pending_Change::Pending_Change( State_Stack::Action action, States::ID state_id )
    : _action( action )
      , _state_id( state_id )
{
}
