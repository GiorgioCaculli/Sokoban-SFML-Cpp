#include "CommandQueue.hpp"
#include "Scene_Node.hpp"

using namespace sokoban::ui::gui;

void CommandQueue::push( const Command &command )
{
    _queue.push( command );
}

Command CommandQueue::pop()
{
    Command command = _queue.front();

    _queue.pop();

    return command;
}

bool CommandQueue::is_empty() const
{
    return _queue.empty();
}
