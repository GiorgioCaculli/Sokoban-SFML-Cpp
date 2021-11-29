#ifndef SOKOBAN_RESOURCE_HOLDER_HPP
#define SOKOBAN_RESOURCE_HOLDER_HPP

#include <map>
#include <memory>
#include <string>
#include <cassert>
#include <stdexcept>

namespace sokoban
{
    namespace ui
    {
        template< typename Resource, typename Identifier >
            class Resource_Holder
            {
            public:
                void load( Identifier id, const std::string &filename );
                template< typename Parameter >
                    void load( Identifier id, const std::string &filename, const Parameter &second_param );
                Resource &get( Identifier id );
                const Resource &get( Identifier id ) const;
            private:
                std::map< Identifier, std::unique_ptr< Resource > > _resource_map;
                void insert_resource( Identifier id, std::unique_ptr< Resource > resource );
            };

#include "Resource_Holder.inl"

    }
}

#endif //SOKOBAN_RESOURCE_HOLDER_HPP
