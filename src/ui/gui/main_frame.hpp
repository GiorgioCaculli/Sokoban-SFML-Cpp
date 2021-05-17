#ifndef SOKOBAN_MAIN_FRAME_HPP
#define SOKOBAN_MAIN_FRAME_HPP

#include <GLFW/glfw3.h>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class MainFrame
            {
            private:
                GLFWwindow *window;
                int _width{};
                int _height{};
                int _result_code{};
            public:
                MainFrame( int width, int height );

                MainFrame();

                void set_width( int width );

                int get_width() const;

                void set_height( int height );

                int get_height() const;

                int glfw_result_code() const;
            };
        }
    }
}


#endif //SOKOBAN_MAIN_FRAME_HPP
