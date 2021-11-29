
template< typename Resource, typename Identifier >
    void Resource_Holder< Resource, Identifier >::load( Identifier id, const std::string &filename )
    {
        // Create and load resource
        std::unique_ptr< Resource > resource( new Resource() );
        if ( !resource->loadFromFile( filename ) )
        {
            throw std::runtime_error( "Resource_Holder::load - Failed to load " + filename );
        }

        // If loading successful, insert resource to map
        insert_resource( id, std::move( resource ) );
    }

template< typename Resource, typename Identifier >
template< typename Parameter >
    void Resource_Holder< Resource, Identifier >::load( Identifier id, const std::string &filename, const Parameter &second_param )
    {
        // Create and load resource
        std::unique_ptr< Resource > resource( new Resource() );
        if ( !resource->loadFromFile( filename, second_param ) )
        {
            throw std::runtime_error( "Resource_Holder::load - Failed to load " + filename );
        }

        // If loading successful, insert resource to map
        insert_resource( id, std::move( resource ) );
    }

template< typename Resource, typename Identifier >
    Resource &Resource_Holder< Resource, Identifier >::get( Identifier id )
    {
        auto found = _resource_map.find( id );
        assert( found != _resource_map.end() );

        return *found->second;
    }

template< typename Resource, typename Identifier >
    const Resource &Resource_Holder< Resource, Identifier >::get( Identifier id ) const
    {
        auto found = _resource_map.find( id );
        assert( found != _resource_map.end() );

        return *found->second;
    }

template< typename Resource, typename Identifier >
    void Resource_Holder< Resource, Identifier >::insert_resource( Identifier id, std::unique_ptr< Resource > resource )
    {
        // Insert and check success
        auto inserted = _resource_map.insert( std::make_pair( id, std::move( resource ) ) );
        assert( inserted.second );
    }
