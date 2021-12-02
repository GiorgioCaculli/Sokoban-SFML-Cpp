#pragma once
#ifndef SOKOBAN_STATE_HPP
#define SOKOBAN_STATE_HPP

#include "State_Identifiers.hpp"
#include "../Resource_Identifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
    class RenderWindow;
}

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Stack;

            class Entity_Player;

            class State
            {
            public:
                typedef std::unique_ptr< State > Ptr;

                struct Context
                {
                    Context( sf::RenderWindow &window, Texture_Holder &textures, Font_Holder &fonts );
                    sf::RenderWindow *_window;
                    Texture_Holder *_textures;
                    Font_Holder *_fonts;
                };

                State( State_Stack &stack, Context context );
                virtual ~State();
                virtual void draw() = 0;
                virtual bool update( sf::Time dt ) = 0;
                virtual bool handle_event( const sf::Event &event ) = 0;
            protected:
                void request_stack_push( States::ID stateID );
                void request_stack_pop();
                void request_state_clear();
                Context get_context() const;
            private:
                State_Stack *_stack;
                Context _context;
            };
        }
    }
}

#endif //SOKOBAN_STATE_HPP
