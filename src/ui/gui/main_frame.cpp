#include "main_frame.hpp"

using namespace sokoban::ui::gui;

MainFrame::MainFrame( int width, int height )
{
    set_width( width );
    set_height( height );
}

MainFrame::MainFrame()
: MainFrame( 800, 600 )
{

}

void MainFrame::set_width( int width )
{
    this->_width = width;
}

int MainFrame::get_width() const
{
    return _width;
}

void MainFrame::set_height( int height )
{
    this->_height = height;
}

int MainFrame::get_height() const
{
    return _height;
}
