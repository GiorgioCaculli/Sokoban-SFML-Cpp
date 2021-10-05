#include "User.hpp"
#include "../resource_holder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace sokoban::ui::gui;

Textures::ID to_texture_id( User::Face face )
{
    switch ( face )
    {
    case User::Player_North:
        return Textures::Player_North;
    case User::Player_South:
        return Textures::Player_South;
    case User::Player_East:
        return Textures::Player_East;
    case User::Player_West:
        return Textures::Player_West;
    }
    return Textures::Player_South;
}

User::User( User::Face face, const TextureHolder &textures )
        : face( face )
          , sprite( textures.get( to_texture_id( face ) ) )
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin( bounds.width / 2.f, bounds.height / 2.f );
}

void User::draw_current( sf::RenderTarget &target, sf::RenderStates states ) const
{
    target.draw( sprite, states );
}
