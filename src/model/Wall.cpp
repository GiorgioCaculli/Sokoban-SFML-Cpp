#include "Wall.hpp"

#include "../util/Logger.hpp"

#include <sstream>
#include <iostream>

using namespace sokoban::model;
using namespace sokoban::util;

/**
 * Default constructor for the walls
 * @param x The X coordinate on the board
 * @param y The Y coordinate on the board
 */
Wall::Wall( float x, float y )
        : Actor( x, y )
{
}

/**
 * Copy constructor for the wall
 * @param wall The wall we wish to copy the information from
 */
Wall::Wall( const Wall &wall )
        : Wall( wall.get_x(), wall.get_y() )
{
}

/**
 * Redefinition of the = operator
 * @param wall The wall we wish to copy the information from
 * @return The new instance of wall with the copied information
 */
Wall &Wall::operator=( const Wall &wall )
{
    if ( &wall != this )
    {
        set_x( wall.get_x() );
        set_y( wall.get_y() );
    }
    return *this;
}

/**
 * Default destructor for the wall actor
 */
Wall::~Wall()
{
    Logger::log( LoggerLevel::INFO, "Deletion " + Wall::to_string() );
}

/**
 * Get the nature of a wall
 * @return The fact that it is a wall actor
 */
Actor::ID Wall::get_type() const
{
    return Actor::WALL;
}

/**
 * Textual output stating the wall's information
 * @return The textual output with the wall's information
 */
std::string Wall::to_string() const
{
    std::stringstream ss;
    ss << "Wall: " << Actor::to_string();
    return ss.str();
}

/**
 * Redefinition of the << operator
 * @param os The desired output stream
 * @param wall The wall we wish to output
 * @return Textual output containing the wall's information
 */
std::ostream &sokoban::model::operator<<( std::ostream &os, const Wall &wall )
{
    os << wall.to_string();
    return os;
}
