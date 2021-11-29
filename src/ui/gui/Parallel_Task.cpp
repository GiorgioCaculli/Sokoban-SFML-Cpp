#include "Parallel_Task.hpp"

using namespace sokoban::ui::gui;

Parallel_Task::Parallel_Task()
        : _thread( &Parallel_Task::run_task, this )
          , _finished( false )
{

}

void Parallel_Task::execute()
{
    _finished = false;
    _elapsed_time.restart();
    _thread.launch();
}

bool Parallel_Task::is_finished()
{
    sf::Lock lock( _mutex );
    return _finished;
}

float Parallel_Task::get_completion()
{
    sf::Lock lock( _mutex );
    return _elapsed_time.getElapsedTime().asSeconds() / 10.f;
}

void Parallel_Task::run_task()
{
    bool ended = false;
    while ( !ended )
    {
        sf::Lock lock( _mutex );
        if ( _elapsed_time.getElapsedTime().asSeconds() >= 10.f )
        {
            ended = true;
        }
        {
            sf::Lock lock( _mutex );
            _finished = true;
        }
    }
}
