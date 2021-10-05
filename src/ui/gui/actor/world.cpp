#include "world.hpp"

using namespace sokoban::ui::gui;

World::World( sf::RenderWindow &window )
        : window( window )
          , world_view( window.getDefaultView() )
          , textures()
          , scene_graph()
          , scene_layers()
          , world_bounds( 0.f, 0.f, world_view.getSize().x, world_view.getSize().y )
          , spawn_position( world_view.getSize().x / 2.f, world_bounds.height - world_view.getSize().y / 2.f )
          , scroll_speed( 0.f )
          , player( nullptr )
{
    load_textures();
    build_scene();
    world_view.setCenter( spawn_position );
}

void World::update( sf::Time dt )
{
    world_view.move( 0.f, scroll_speed * dt.asSeconds() );
    sf::Vector2f position = player->getPosition();
    sf::Vector2f velocity = player->get_velocity();

    if ( position.x <= world_bounds.left + 150.f || position.x >= world_bounds.left + world_bounds.width - 150.f )
    {
        velocity.x = -velocity.x;
        player->set_velocity( velocity );
    }
    scene_graph.update( dt );
}

void World::draw()
{
    window.setView( world_view );
    window.draw( scene_graph );
}

void World::load_textures()
{
    textures.load( Textures::Player_North, "assets/images/PNG/Character7.png" );
    textures.load( Textures::Player_South, "assets/images/PNG/Character4.png" );
    textures.load( Textures::Player_West, "assets/images/PNG/Character1.png" );
    textures.load( Textures::Player_East, "assets/images/PNG/Character2.png" );
    textures.load( Textures::Box, "assets/images/PNG/Crate_Brown.png" );
    textures.load( Textures::Platform, "assets/images/PNG/EndPoint_Purple.png" );
    textures.load( Textures::Wall, "assets/images/PNG/Wall_Gray.png" );
    textures.load( Textures::Floor, "assets/images/PNG/GroundGravel_Concrete.png" );
}

void World::build_scene()
{
    for ( std::size_t i = 0; i < LayerCount; ++i )
    {
        SceneNode::Ptr layer( new SceneNode() );
        scene_layers[ i ] = layer.get();

        scene_graph.attach_child( std::move( layer ) );
    }

    sf::Texture &texture = textures.get( Textures::Floor );
    sf::IntRect texture_rect( world_bounds );
    texture.setRepeated( true );

    std::unique_ptr< SpriteNode > background_sprite( new SpriteNode( texture, texture_rect ) );
    background_sprite->setPosition( world_bounds.left, world_bounds.top );
    scene_layers[ Background ]->attach_child( std::move( background_sprite ) );

    std::unique_ptr< User > player1( new User( User::Player_South, textures ) );
    player = player1.get();
    player->setPosition( spawn_position );
    player->set_velocity( 40.f, scroll_speed );
    scene_layers[ Actor ]->attach_child( std::move( player1 ) );
}
