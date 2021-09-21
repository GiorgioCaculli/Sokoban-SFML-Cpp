#ifndef SOKOBAN_RESOURCE_HOLDER_HPP
#define SOKOBAN_RESOURCE_HOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <ostream>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            template< typename Resource, typename Identifier >
            class ResourceHolder
            {
            public:
                void load( Identifier id, const std::string &file_name );
                template< typename Parameter >
                void load( Identifier id, const std::string &file_name, const Parameter &second_param );
                Resource &get( Identifier id );
                const Resource &get( Identifier id ) const;
            private:
                std::map< Identifier, std::unique_ptr< Resource > > resource_map;
            private:
                void init_resource( Identifier id, std::unique_ptr< Resource > resource );
            };
        }
    }
}

#include "resource_holder.inl"

#endif //SOKOBAN_RESOURCE_HOLDER_HPP
