#include "Base_State.hpp"

using namespace sokoban::ui::gui;

Base_State::Base_State( State_Manager *state_manager )
        : _state_manager( state_manager )
          , _transparent( false )
          , _transcendent( false )
{
}

Base_State::~Base_State()
= default;

void Base_State::set_transparent( const bool &transparent )
{
    _transparent = transparent;
}

bool Base_State::is_transparent() const
{
    return _transparent;
}

void Base_State::set_transcendent( const bool &transcendence )
{
    _transcendent = transcendence;
}

bool Base_State::is_transcendent() const
{
    return _transcendent;
}

State_Manager *Base_State::get_state_manager()
{
    return _state_manager;
}
