#include <ui/gui/ResourceBundle.hpp>
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
    : Resource_Bundle( "res/locale/strings.json", "en_US.UTF8")
{
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

    return value;
}

std::string Resource_Bundle::get_path() const
{
    return _path;
}

std::locale Resource_Bundle::get_locale() const
{
    return _locale;
}
