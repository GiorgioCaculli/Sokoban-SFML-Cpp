#ifndef SOKOBAN_PARALLEL_TASK_HPP
#define SOKOBAN_PARALLEL_TASK_HPP

#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Parallel_Task
            {
            public:
                Parallel_Task();
                void execute();
                bool is_finished();
                float get_completion();
            private:
                sf::Thread _thread;
                bool _finished;
                sf::Clock _elapsed_time;
                sf::Mutex _mutex;
                void run_task();
            };
        }
    }
}

#endif //SOKOBAN_PARALLEL_TASK_HPP
