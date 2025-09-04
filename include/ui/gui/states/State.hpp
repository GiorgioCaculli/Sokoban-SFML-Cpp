#pragma once
#ifndef SOKOBAN_STATE_HPP
#define SOKOBAN_STATE_HPP

#include <ui/gui/states/State_Identifiers.hpp>
#include <ui/gui/Resource_Identifiers.hpp>
#include <ui/gui/Resource_Bundle.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

#include "input/Keyboard.hpp"
#include "input/Mouse.hpp"

/**
 * Pre declaration of the SFML RenderWindow class
 */
namespace sf
{
    class RenderWindow;
}


namespace sokoban::ui::gui
{
    class State_Stack; /** The stack containing the various states */
    class Music_Player; /** The global music player */
    class Sound_Player; /** The global sound effects player */
    class State
    {
    public:
        /** Unique pointer that characterizes the base nature of a state */
        typedef std::unique_ptr< State > Ptr;

        /**
         * Public struct containing globally accessible variables
         */
        struct Context
        {
            Context( sf::RenderWindow& window, Texture_Holder& textures, Font_Holder& fonts,
                     Music_Player& music, Sound_Player& sounds, Resource_Bundle& resources, input::Keyboard& keyboard, input::Mouse& mouse );

            sf::RenderWindow* _window;
            Texture_Holder* _textures;
            Font_Holder* _fonts;
            Music_Player* _music;
            Sound_Player* _sounds;
            Resource_Bundle* _resource_bundle;
            input::Keyboard *_keyboard;
            input::Mouse *_mouse;
        };

        State( State_Stack& stack, const Context& context );

        virtual ~State();

        virtual void draw() = 0;

        virtual bool update( sf::Time dt ) = 0;

        virtual bool handle_event( const sf::Event& event ) = 0;

    protected:
        void request_stack_push( States::ID stateID ) const;

        void request_stack_pop() const;

        void request_state_clear() const;

        [[nodiscard]] Context get_context() const;

    private:
        State_Stack* _stack; /** The stack containing the various states */
        Context _context; /** The globally accessible context */
    };
}


#endif //SOKOBAN_STATE_HPP
