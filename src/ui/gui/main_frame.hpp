#ifndef SOKOBAN_MAIN_FRAME_HPP
#define SOKOBAN_MAIN_FRAME_HPP
#include "../../util/logger.hpp"

#include <GLFW/glfw3.h>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            using namespace sokoban::util;
            class MainFrame
            {
            private:
                GLFWwindow *window;
                int _width{};
                int _height{};
                int _result_code{};
                Logger *logger{};
            public:
                MainFrame( int width, int height );

                MainFrame();

                ~MainFrame();

                void set_width( int width );

                int get_width() const;

                void set_height( int height );

                int get_height() const;

                int launch() const;
            };
        }
    }
}


#endif //SOKOBAN_MAIN_FRAME_HPP
