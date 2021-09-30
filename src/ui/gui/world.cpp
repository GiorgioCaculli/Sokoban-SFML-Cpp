#include "world.hpp"

using namespace sokoban::ui::gui;

World::World( sf::RenderWindow &window )
        :window( window ), world_view( window.getDefaultView() ), textures(), scene_graph(), scene_layers(),
         world_bounds( 0.f, 0.f, world_view.getSize().x, 2000.f ),
         spawn_position( world_view.getSize().x / 2.f, world_bounds.height - world_view.getSize().y / 2.f ),
         scroll_speed( -50.f ), player( nullptr )
{
    load_textures();
    build_scene();
    world_view.setCenter( spawn_position );
}

void World::update( sf::Time dt )
{
    world_view.move( 0.f, scroll_speed * dt.asSeconds() );
    sf::Vector2f velocity = player->get_velocity();
}

void World::draw()
{
    window.setView( world_view );
    window.draw( scene_graph );
}

void World::load_textures()
{
    textures.load( Textures::Player_North, "" );
    textures.load( Textures::Player_South, "" );
    textures.load( Textures::Player_West, "" );
    textures.load( Textures::Player_East, "" );
    textures.load( Textures::Box, "" );
    textures.load( Textures::Platform, "" );
    textures.load( Textures::Wall, "" );
    textures.load( Textures::Background, "" );
}

void World::build_scene()
{
    for( std::size_t i = 0; i < LayerCount; ++i )
    {
        SceneNode::Ptr layer( new SceneNode() );
        scene_layers[ i ] = layer.get();

        scene_graph.attach_child( std::move( layer ) );
    }

    sf::Texture &texture = textures.get( Textures::Background );
    sf::IntRect texture_rect( world_bounds );
    texture.setRepeated( true );

    std::unique_ptr< SpriteNode > background_sprite( new SpriteNode( texture, texture_rect ) );
    background_sprite->setPosition( world_bounds.left, world_bounds.top );
    scene_layers[ Background ]->attach_child( std::move( background_sprite) );

    std::unique_ptr< Player > p( new Player( Player::South, textures ) );
    player = p.get();
    player->set_position( spawn_position );
    player->set_velocity( 40.f, scroll_speed );
    scene_layers[ Floor ]->attach_child( std::move( p ) );


}
