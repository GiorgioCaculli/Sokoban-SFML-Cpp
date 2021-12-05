#ifndef SOKOBAN_UTILITY_INL
#define SOKOBAN_UTILITY_INL

template< typename T >
    std::string to_string( const T &value )
    {
        std::stringstream stream;
        stream << value;
        return stream.str();
    }

#endif //SOKOBAN_UTILITY_INL
