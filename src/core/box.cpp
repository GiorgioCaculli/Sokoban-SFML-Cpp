#include "box.hpp"

using namespace sokoban::core;

Box::Box( int x, int y )
        :
        Actor( x, y )
{
    init_box();
}

Box::~Box()
= default;

void Box::init_box()
{

}

void Box::move( int x, int y )
{
    setX( getX() + x );
    setY( getY() + y );
}
