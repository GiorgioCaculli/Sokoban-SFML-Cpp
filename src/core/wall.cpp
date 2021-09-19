#include "wall.hpp"
#include "../util/logger.hpp"

using namespace sokoban::core;
using namespace sokoban::util;

Wall::Wall( float x, float y )
        :Actor( x, y )
{
    init_wall();
}

Wall::~Wall()
= default;

void Wall::init_wall()
{
    texture = new sf::Texture();
    texture->loadFromFile( "assets/images/PNG/Wall_Gray.png" );
    set_texture( texture );
}
