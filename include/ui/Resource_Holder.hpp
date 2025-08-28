#ifndef SOKOBAN_RESOURCE_HOLDER_HPP
#define SOKOBAN_RESOURCE_HOLDER_HPP

#include <map>
#include <memory>
#include <string>
#include <cassert>
#include <stdexcept>


namespace sokoban::ui
{
    /**
     * Resource holder meant to manage various natures of a Resource.
     * @tparam Resource Could be a Sprite or a Sound
     * @tparam Identifier Unique identifier in an enum
     */
    template< typename Resource, typename Identifier >
    class Resource_Holder
    {
    public:
        /** Loads the requested asset based on its ID and filename */
        void load( Identifier id, const std::string& filename );

        template< typename Parameter >
        /** Loads the requested asset based on its ID and filename plus force a parameter */
        void load( Identifier id, const std::string& filename, const Parameter& second_param );

        /** Resource getter meant to ensure the retrieval of a non-const Resource */
        Resource& get( Identifier id );

        /** Resource getter meant to ensure the retrieval of a const Resource */
        const Resource& get( Identifier id ) const;

    private:
        /** Map containing the various resources */
        std::map< Identifier, std::unique_ptr< Resource > > _resource_map;

        /** Insertion of resource into map upon execution of load */
        void insert_resource( Identifier id, std::unique_ptr< Resource > resource );
    };

#include "Resource_Holder.inl"
}


#endif //SOKOBAN_RESOURCE_HOLDER_HPP
