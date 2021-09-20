
#include <rdf_node.h>

template< typename Resource, typename Identifier >
void ResourceHolder< Resource, Identifier >::load( Identifier id, const std::string &file_name )
{
    std::unique_ptr< Resource > resource( new Resource() );
    if( !resource->loadFromFile( file_name ) )
    {
        throw std::runtime_error( "ResourceHolder::load - failed to load" + file_name );
    }
    insertResource( id, std::move( resource ) );
}
