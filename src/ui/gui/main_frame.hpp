#ifndef SOKOBAN_MAIN_FRAME_HPP
#define SOKOBAN_MAIN_FRAME_HPP

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class MainFrame
            {
            private:
                int _width{};
                int _height{};
            public:
                MainFrame( int width, int height );
                MainFrame();
                void set_width( int width );
                int get_width() const;
                void set_height( int height );
                int get_height() const;
            };
        }
    }
}


#endif //SOKOBAN_MAIN_FRAME_HPP
