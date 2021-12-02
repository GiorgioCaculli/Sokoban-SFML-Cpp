#include "State_Stack.hpp"

#include <cassert>

using namespace sokoban::ui::gui;

State_Stack::State_Stack( State::Context context )
: _stack()
, _pending_list()
, _context( context )
, _factories()
{
}

void State_Stack::update( sf::Time dt )
{
    for( auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr )
    {
        if( !( *itr )->update( dt ) )
        {
            break;
        }
    }
    apply_pending_changes();
}

void State_Stack::draw()
{
    for( State::Ptr &state : _stack )
    {
        state->draw();
    }
}

void State_Stack::handle_event( const sf::Event &event )
{
    for( auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr )
    {
        if( !( *itr )->handle_event( event ) )
        {
            break;
        }
    }
    apply_pending_changes();
}

void State_Stack::push_state( States::ID state_id )
{
    _pending_list.emplace_back( Push, state_id );
}

void State_Stack::pop_state()
{
    _pending_list.emplace_back( Pop );
}

void State_Stack::clear_states()
{
    _pending_list.emplace_back( Clear );
}

bool State_Stack::is_empty() const
{
    return _stack.empty();
}

State::Ptr State_Stack::create_state( States::ID state_id )
{
    auto found = _factories.find( state_id );
    assert( found != _factories.end() );
    return found->second();
}

void State_Stack::apply_pending_changes()
{
    for( Pending_Change change : _pending_list )
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
}

State_Stack::Pending_Change::Pending_Change( State_Stack::Action action, States::ID state_id )
: _action( action )
, _state_id( state_id )
{

}
