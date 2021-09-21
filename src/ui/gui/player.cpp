#include "player.hpp"

#include "entity.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace sokoban::ui::gui;

Textures::ID to_texture_id( Player::Face face )
{
    switch ( face )
    {
    case Player::North:
        return Textures::Player_North;
    case Player::South:
        return Textures::Player_South;
    case Player::East:
        return Textures::Player_East;
    case Player::West:
        return Textures::Player_West;
    }
    return Textures::Player_South;
}

Player::Player( Player::Face face, const TextureHolder& textures )
        :face( face ), sprite( textures.get( to_texture_id( face ) ) )
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin( bounds.width / 2.f, bounds.height / 2.f );
}

void Player::draw_current( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw( sprite, states );
}
