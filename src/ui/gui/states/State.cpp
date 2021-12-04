#include "State.hpp"

#include "State_Stack.hpp"

using namespace sokoban::ui::gui;

State::Context::Context( sf::RenderWindow &window, Texture_Holder &textures, Font_Holder &fonts, Music_Player &music, Sound_Player &sounds )
        : _window( &window )
          , _textures( &textures )
          , _fonts( &fonts )
          , _music( &music )
          , _sounds( &sounds )
{
}

State::State( State_Stack &stack, State::Context context )
        : _stack( &stack )
          , _context( context )
{
}

State::~State()
= default;

void State::request_stack_push( States::ID stateID )
{
    _stack->push_state( stateID );
}

void State::request_stack_pop()
{
    _stack->pop_state();
}

void State::request_state_clear()
{
    _stack->clear_states();
}

State::Context State::get_context() const
{
    return _context;
}
