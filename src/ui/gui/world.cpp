#include "world.hpp"

using namespace sokoban::ui::gui;

World::World( sf::RenderWindow& window )
: window( window )
, world_view( window.getDefaultView() )
, textures()
, scene_graph()
, scene_layers()
, world_bounds( 0.f, 0.f, world_view.getSize().x, 2000.f )
, spawn_position( world_view.getSize().x / 2.f, world_bounds.height - world_view.getSize().y / 2.f )
, scroll_speed( -50.f )
, player( nullptr )
{
    load_textures();
    build_scene();
    world_view.setCenter( spawn_position );
}

void World::update( sf::Time dt )
{

}

void World::draw()
{
    window.setView( world_view );
    window.draw( scene_graph );
}

void World::load_textures()
{

}

void World::build_scene()
{

}
