#include "Platform.hpp"

#include "../util/Logger.hpp"

#include <sstream>
#include <iostream>

using namespace sokoban::model;
using namespace sokoban::util;

/**
 * Default constructor for the platforms
 * @param x The X coordinates on the board
 * @param y The Y coordinates on the board
 */
Platform::Platform( float x, float y )
        : Actor( x, y )
{
}

/**
 * Copy constructor for the platform actor
 * @param platform The platform we wish to copy the information from
 */
Platform::Platform( const Platform &platform )
        : Platform( platform.get_x(), platform.get_y() )
{
}

/**
 * Redefinition of the = operator
 * @param platform The platform we wish to copy the information from
 * @return New instance of a platform with the copied information
 */
Platform &Platform::operator=( const Platform &platform )
{
    if ( &platform != this )
    {
        set_x( platform.get_x() );
        set_y( platform.get_y() );
    }
    return *this;
}

/**
 * Default destructor for the platforms
 */
Platform::~Platform()
{
    Logger::log( LoggerLevel::INFO, "Deletion " + Platform::to_string() );
}

/**
 * Getter meant to retrieve the nature of a platform actor
 * @return The fact that the actor is actually a platform
 */
Actor::ID Platform::get_type() const
{
    return Actor::PLATFORM;
}

/**
 * Textual output containing the platform's information
 * @return Text containing the info
 */
std::string Platform::to_string() const
{
    std::stringstream ss;
    ss << "Platform: " << Actor::to_string();
    return ss.str();
}

/**
 * Redefinition of the << operator
 * @param os The desired output stream
 * @param platform The platform we wish to output
 * @return Textual output displaying the platform's information
 */
std::ostream &sokoban::model::operator<<( std::ostream &os, const Platform &platform )
{
    os << platform.to_string();
    return os;
}
