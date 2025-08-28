#ifndef SOKOBAN_UTILITY_INL
#define SOKOBAN_UTILITY_INL

/**
 * Function meant to return a stringstream to stream.
 * @tparam T The nature of the entity that will call this function
 * @param value The value to insert into the stringstream
 * @return The stringstream in string format
 */
template< typename T >
std::string to_string( const T& value )
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

#endif //SOKOBAN_UTILITY_INL
