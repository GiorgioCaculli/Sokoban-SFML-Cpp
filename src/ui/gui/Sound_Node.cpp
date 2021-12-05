#include "Sound_Node.hpp"

#include "Sound_Player.hpp"

using namespace sokoban::ui::gui;

Sound_Node::Sound_Node( Sound_Player &player )
: Scene_Node()
, _sounds( player )
{
}

void Sound_Node::play_sound( Sound_Effect::ID sound, sf::Vector2f position )
{
    _sounds.play( sound, position );
}

unsigned int Sound_Node::get_category() const
{
    return Category::Sound_Effect;
}
