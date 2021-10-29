#pragma once
#ifndef SOKOBAN_BASE_STATE_HPP
#define SOKOBAN_BASE_STATE_HPP

#include <SFML/Graphics.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class State_Manager;

            class Base_State
            {
                friend class State_Manager;

            public:
                Base_State( State_Manager *state_manager );
                virtual ~Base_State();
                virtual void on_create() = 0;
                virtual void on_destroy() = 0;
                virtual void activate() = 0;
                virtual void deactivate() = 0;
                virtual void update( const sf::Time &dt ) = 0;
                void set_transparent( const bool &transparent );
                bool is_transparent() const;
                void set_transcendent( const bool &transcendence );
                bool is_transcendent() const;
                State_Manager *get_state_manager();
            private:
                State_Manager *_state_manager;
                bool _transparent;
                bool _transcendent;
            };
        }
    }
}

#endif //SOKOBAN_BASE_STATE_HPP
