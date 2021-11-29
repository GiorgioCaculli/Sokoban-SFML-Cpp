#ifndef SOKOBAN_COMMANDQUEUE_HPP
#define SOKOBAN_COMMANDQUEUE_HPP

#include "Command.hpp"

#include <queue>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class CommandQueue
            {
            public:
                void push( const Command &command );
                Command pop();
                bool is_empty() const;
            private:
                std::queue< Command > _queue;
            };
        }
    }
}

#endif //SOKOBAN_COMMANDQUEUE_HPP
