#include <gzc/games/sokoban/ui/gui/sfml/Sound_Node.hpp>

#include <gzc/games/sokoban/ui/gui/sfml/Sound_Player.hpp>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the sound node
 * @param player The Sound Player that interacts with the node
 */
Sound_Node::Sound_Node( Sound_Player &player )
: Scene_Node()
, _sounds( player )
{
}

/**
 * Function that plays the sound effect based on its ID and position on the map
 * @param sound The sound effect to play
 * @param position The position on the map
 */
void Sound_Node::play_sound( Sound_Effect::ID sound, sf::Vector2f position )
{
    _sounds.play( sound, position );
}

/**
 * Category getter that characterizes the current node
 * @return Its category being a sound effect
 */
unsigned int Sound_Node::get_category() const
{
    return Category::Sound_Effect;
}
