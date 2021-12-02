#ifndef SOKOBAN_STATE_STACK_HPP
#define SOKOBAN_STATE_STACK_HPP

#include "State.hpp"
#include "State_Identifiers.hpp"
#include "../Resource_Identifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <map>
#include <vector>
#include <utility>
#include <functional>

namespace sf
{
    class Event;
    class RenderWindow;
}

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Stack
        : private sf::NonCopyable
            {
            public:
                enum Action
                {
                    Push,
                    Pop,
                    Clear
                };
                explicit State_Stack( State::Context context );
                template< typename T >
                    void register_state( States::ID state_id );
                void update( sf::Time dt );
                void draw();
                void handle_event( const sf::Event &event );
                void push_state( States::ID state_id );
                void pop_state();
                void clear_states();
                bool is_empty() const;
            private:
                State::Ptr create_state( States::ID state_id );
                void apply_pending_changes();
                struct Pending_Change
                {
                    explicit Pending_Change( Action action, States::ID state_id = States::None );
                    Action _action;
                    States::ID _state_id;
                };
                std::vector< State::Ptr > _stack;
                std::vector< Pending_Change > _pending_list;
                State::Context _context;
                std::map< States::ID, std::function< State::Ptr() > > _factories;
            };

            template< typename T >
                void State_Stack::register_state( States::ID state_id )
                {
                    _factories[ state_id ] = [ this ] ()
                    {
                        return State::Ptr( new T( *this, _context ) );
                    };
                }
        }
    }
}

#endif //SOKOBAN_STATE_STACK_HPP
