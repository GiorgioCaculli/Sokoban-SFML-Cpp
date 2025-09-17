#ifndef SOKOBAN_STATE_STACK_HPP
#define SOKOBAN_STATE_STACK_HPP

#include <gui/states/State.hpp>
#include <gui/states/State_Identifiers.hpp>

#include <SFML/System/Time.hpp>

#include <map>
#include <vector>
#include <functional>

namespace sf
{
    class Event;
    class RenderWindow;
}


namespace sokoban::ui::gui
{
    class State_Stack
    {
    public:
        /**
         * The various actions possible with the stack
         */
        enum class Action
        {
            Push, /** Push a state ahead */
            Pop, /** Pop an existing state */
            Clear /** Clear the entirety of the stack */
        };

        explicit State_Stack( const State::Context& context );

        template< typename T >
        void register_state( States::ID state_id );

        void update( sf::Time dt );

        void draw() const;

        void handle_event( const sf::Event& event );

        void push_state( States::ID state_id );

        void pop_state();

        void clear_states();

        [[nodiscard]] bool is_empty() const;

    private:
        State::Ptr create_state( States::ID state_id );

        void apply_pending_changes();

        struct Pending_Change
        {
            explicit Pending_Change( Action action, States::ID state_id = States::ID::None );

            Action _action;
            States::ID _state_id;
        };

        std::vector< State::Ptr > _stack; /** The stack containing the various states */
        std::vector< Pending_Change > _pending_list;
        /** The handler meant to change the state based on an action */
        State::Context _context; /** The globally accessible resources */
        std::map< States::ID, std::function< State::Ptr() > > _factories;
        /** Mapper that defines a State per ID */
    };

    /**
     * Dynamic initialisation of a state upon registration
     * @tparam T The nature of the state
     * @param state_id The ID that characterizes it
     */
    template< typename T >
    void State_Stack::register_state( States::ID state_id )
    {
        _factories[ state_id ] = [ this ]()
        {
            return State::Ptr( new T( *this, _context ) );
        };
    }
}


#endif //SOKOBAN_STATE_STACK_HPP
