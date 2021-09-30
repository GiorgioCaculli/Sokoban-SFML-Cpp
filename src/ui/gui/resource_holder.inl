
namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            template< typename Resource, typename Identifier >
            void ResourceHolder< Resource, Identifier >::load( Identifier id, const std::string &filename )
            {
                // Create and load resource
                std::unique_ptr< Resource > resource( new Resource() );
                if ( !resource->loadFromFile( filename ) )
                    throw std::runtime_error( "ResourceHolder::load - Failed to load " + filename );

                // If loading successful, insert resource to map
                insertResource( id, std::move( resource ) );
            }

            template< typename Resource, typename Identifier >
            template< typename Parameter >
            void ResourceHolder< Resource, Identifier >::load( Identifier id, const std::string &filename,
                    const Parameter &secondParam )
            {
                // Create and load resource
                std::unique_ptr< Resource > resource( new Resource() );
                if ( !resource->loadFromFile( filename, secondParam ) )
                    throw std::runtime_error( "ResourceHolder::load - Failed to load " + filename );

                // If loading successful, insert resource to map
                insertResource( id, std::move( resource ) );
            }

            template< typename Resource, typename Identifier >
            Resource &ResourceHolder< Resource, Identifier >::get( Identifier id )
            {
                auto found = resource_map.find( id );
                assert( found != resource_map.end() );

                return *found->second;
            }

            template< typename Resource, typename Identifier >
            const Resource &ResourceHolder< Resource, Identifier >::get( Identifier id ) const
            {
                auto found = resource_map.find( id );
                assert( found != resource_map.end() );

                return *found->second;
            }

            template< typename Resource, typename Identifier >
            void ResourceHolder< Resource, Identifier >::insert_resource( Identifier id,
                    std::unique_ptr< Resource > resource )
            {
                // Insert and check success
                auto inserted = resource_map.insert( std::make_pair( id, std::move( resource ) ) );
                assert( inserted.second );
            }
        }
    }
}
