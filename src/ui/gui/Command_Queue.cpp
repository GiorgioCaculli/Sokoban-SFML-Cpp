#include "Command_Queue.hpp"
#include "Scene_Node.hpp"

using namespace sokoban::ui::gui;

void Command_Queue::push( const Command &command )
{
    _queue.push( command );
}

Command Command_Queue::pop()
{
    Command command = _queue.front();

    _queue.pop();

    return command;
}

bool Command_Queue::is_empty() const
{
    return _queue.empty();
}
