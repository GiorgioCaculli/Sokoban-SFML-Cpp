#ifndef SOKOBAN_RESOURCEBUNDLE_HPP
#define SOKOBAN_RESOURCEBUNDLE_HPP

#include <fstream>
#include <locale>
#include <vector>

class Resource_Bundle
{
private:
    std::string _path;
    std::locale _locale;
    std::ifstream _file;
    std::pmr::vector< std::string > _strings;

public:
    explicit Resource_Bundle( std::string path, const std::string& locale = "en_US.UTF8" );
    Resource_Bundle();
    ~Resource_Bundle();
    std::string get_string( const std::string& key ) const;
    std::string get_path() const;
    std::locale get_locale() const;
};


#endif //SOKOBAN_RESOURCEBUNDLE_HPP
