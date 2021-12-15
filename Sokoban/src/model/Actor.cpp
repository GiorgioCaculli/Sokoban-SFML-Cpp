#include "Actor.hpp"

#include <sstream>

using namespace sokoban::model;

const float SPACE = 64.f; /** Dans ce cas, les images mesurent 64x64 */

/**
 * This constructor will initialise the different pieces of informations which characterise an actor
 * @param x The X coordinate.
 * @param y The Y coordinate.
 * @param asset_coords The coordinates on the sprite sheet which represent it graphically.
 */
Actor::Actor( float x, float y )
        : _x( x )
          , _y( y )
{
}

/**
 * Copy Constructor
 * @param actor The actor from which we wish to create a copy
 */
Actor::Actor( const Actor &actor )
        : Actor( actor._x, actor._y )
{
}

/**
 * Redefinition of the "=" operator
 * @param actor The actor from which we wish to copy the information
 * @return The new instance of an actor with the same information as the one on the right
 */
Actor &Actor::operator=( const Actor &actor )
{
    if ( &actor != this )
    {
        _x = actor._x;
        _y = actor._y;
    }
    return *this;
}

/**
 * X coordinate getter
 * @return The value of X
 */
float Actor::get_x() const
{
    return _x;
}

/**
 * X coordinate setter
 * @param x The new value of X
 */
void Actor::set_x( float x )
{
    this->_x = x;
}

/**
 * Y coordinate getter
 * @return The value of Y
 */
float Actor::get_y() const
{
    return _y;
}

/**
 * Y coordinate setter
 * @param y The new value of Y
 */
void Actor::set_y( float y )
{
    this->_y = y;
}

/**
 * Function whose purpose is to verify if a left collision took place between two actors.
 * A movable actor will call this function and will check the following cases:
 * Let's assume Actor 1's X coordinates is x1 and Actor 2's X coordinates is x2:
 * Let's assume Actor 1's Y coordinates is y1 and Actor 2's Y coordinates is y2:
 * SPACE represents the amount of space between each object before the collision:
 * If x1 - SPACE = x2 and Y1 = Y2
 * Then a collision on the left took place.
 * @param actor The actor on the left
 * @return true if the collision took place, false otherwise
 */
bool Actor::is_left_collision( const Actor *actor ) const
{
    return get_x() - SPACE == actor->get_x() && get_y() == actor->get_y();
}

/**
 * Function whose purpose is to verify if a right collision took place between two actors.
 * A movable actor will call this function and will check the following cases:
 * Let's assume Actor 1's X coordinates is x1 and Actor 2's X coordinates is x2:
 * Let's assume Actor 1's Y coordinates is y1 and Actor 2's Y coordinates is y2:
 * SPACE represents the amount of space between each object before the collision:
 * If x1 + SPACE = x2 and y1 = y2
 * Then a collision on the right took place.
 * @param actor The actor on the right
 * @return true if the collision took place, false otherwise
 */
bool Actor::is_right_collision( const Actor *actor ) const
{
    return get_x() + SPACE == actor->get_x() && get_y() == actor->get_y();
}

/**
 * Function whose purpose is to verify if a top collision took place between two actors.
 * A movable actor will call this function and will check the following cases:
 * Let's assume Actor 1's X coordinates is x1 and Actor 2's X coordinates is x2:
 * Let's assume Actor 1's Y coordinates is y1 and Actor 2's Y coordinates is y2:
 * SPACE represents the amount of space between each object before the collision:
 * If y1 - SPACE = y2 and x1 = x2
 * Then a collision on the top took place.
 * @param actor The actor on the top
 * @return true if the collision took place, false otherwise
 */
bool Actor::is_top_collision( const Actor *actor ) const
{
    return get_y() - SPACE == actor->get_y() && get_x() == actor->get_x();
}

/**
 * Function whose purpose is to verify if a bottom collision took place between two actors.
 * A movable actor will call this function and will check the following cases:
 * Let's assume Actor 1's X coordinates is x1 and Actor 2's X coordinates is x2:
 * Let's assume Actor 1's Y coordinates is y1 and Actor 2's Y coordinates is y2:
 * SPACE represents the amount of space between each object before the collision:
 * If y1 + SPACE = y2 and x1 = x2
 * Then a collision on the bottom took place.
 * @param actor The actor on the bottom
 * @return true if the collision took place, false otherwise
 */
bool Actor::is_bottom_collision( const Actor *actor ) const
{
    return get_y() + SPACE == actor->get_y() && get_x() == actor->get_x();
}

/**
 * Textual output for the actor's coordinates
 * @return X: <the value of the x coordinate> Y: <the value of the y coordinate>
 */
std::string Actor::to_string() const
{
    std::stringstream ss;
    ss << "X: " << _x << " Y: " << _y;
    return ss.str();
}

/**
 * Redefinition of the == operator
 * This will allow us to check whether or not two actors are exactly the same.
 * @return true if same actor, false if not
 */
bool Actor::operator==( const Actor &actor ) const
{
    return _x == actor._x &&
            _y == actor._y;
}

/**
 * Redefinition of the != operator
 * This will allow us to check whether two actors are not the same
 * @return the opposite of the == operator
 */
bool Actor::operator!=( const Actor &actor ) const
{
    return !( actor == *this );
}
