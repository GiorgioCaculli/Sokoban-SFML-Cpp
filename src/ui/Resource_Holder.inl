
/**
 * Function meant to load a resource inside the map containing the various assets
 * @tparam Resource The type of resource
 * @tparam Identifier Its unique identifier in the enum
 * @param id Its unique identifier in the enum
 * @param filename The filename of the asset
 */
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

/**
 * Function meant to load an asset with a specific parameter that characterizes it.
 * @tparam Resource The type of resource to load
 * @tparam Identifier Its unique identifier within the enum
 * @tparam Parameter The nature of the parameter
 * @param id Its unique identifier within the enum
 * @param filename The filename of the asset
 * @param second_param The parameter that characterizes the asset
 */
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

/**
 * Getter for the asset based on its unique identifier within an enum from a non-const Resource
 * @tparam Resource The type of resource to retrieve
 * @tparam Identifier Its unique identifier within the enum
 * @param id Its unique identifier within the enum
 * @return The asset requested
 */
template< typename Resource, typename Identifier >
    Resource &Resource_Holder< Resource, Identifier >::get( Identifier id )
    {
        auto found = _resource_map.find( id );
        assert( found != _resource_map.end() );

        return *found->second;
    }

/**
 * Getter for the asset based on its unique identifier within an enum from a const Resource
 * @tparam Resource The type of resource to retrieve
 * @tparam Identifier Its unique identifier within the enum
 * @param id Its unique identifier within the enum
 * @return The asset requested
 */
template< typename Resource, typename Identifier >
    const Resource &Resource_Holder< Resource, Identifier >::get( Identifier id ) const
    {
        auto found = _resource_map.find( id );
        assert( found != _resource_map.end() );

        return *found->second;
    }

/**
 * Function meant to insert a new resource inside the Resource Holder's map
 * @tparam Resource The nature of the Resource
 * @tparam Identifier Its unique identifier within the enum
 * @param id Its unique identifier within the enum
 * @param resource The Resource we want to insert
 */
template< typename Resource, typename Identifier >
    void Resource_Holder< Resource, Identifier >::insert_resource( Identifier id, std::unique_ptr< Resource > resource )
    {
        // Insert and check success
        auto inserted = _resource_map.insert( std::make_pair( id, std::move( resource ) ) );
        assert( inserted.second );
    }
