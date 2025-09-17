#include <format>
#include <gui/Resource_Bundle.hpp>
#include <utility>

Resource_Bundle::Resource_Bundle( std::string path, const std::string& locale )
    : _path( std::move( path ) )
    , _locale( locale )
    , _file( path )
{
    std::string line;
    while ( getline( _file, line ) )
    {
        _strings.push_back( line );
    }
    _file.close();
}

Resource_Bundle::Resource_Bundle()
    : Resource_Bundle( "res/locale/strings.json", "en_US.UTF-8")
{
}

/* TODO: Remove hard coded EN_US locale string */
Resource_Bundle::Resource_Bundle( const Resource_Bundle& r )
: Resource_Bundle(r.get_path(), "en_US.UTF-8" )
{
}

Resource_Bundle& Resource_Bundle::operator=( const Resource_Bundle& r )
{
    if( this != &r )
    {
        _path = r._path;
        _locale = r._locale;
    }
    return *this;
}

Resource_Bundle::~Resource_Bundle()
{
}

std::string Resource_Bundle::get_string( const std::string& key ) const
{
    std::string value;

    if ( key == value )
    {
        return value;
    }

    return "";
}

std::string Resource_Bundle::get_path() const
{
    return _path;
}

std::locale Resource_Bundle::get_locale() const
{
    return _locale;
}
