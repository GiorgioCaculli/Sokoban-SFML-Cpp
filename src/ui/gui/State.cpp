#include "State.hpp"

#include "State_Stack.hpp"

using namespace sokoban::ui::gui;

State::Context::Context( sf::RenderWindow &window, sokoban::ui::Texture_Holder &textures, sokoban::ui::Font_Holder &fonts, Entity_Player &entity_player )
        : _window( &window )
          , _textures( &textures )
          , _fonts( &fonts )
          , _entity_player( &entity_player )
{
}

State::State( State_Stack &stack, State::Context context )
        : _stack( &stack )
          , _context( context )
{
}

State::~State()
{
}

void State::request_stack_push( States::ID stateID )
{
}

void State::request_stack_pop()
{
}

void State::request_state_clear()
{

}

State::Context State::get_context() const
{
    return _context;
}
