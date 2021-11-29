#ifndef SOKOBAN_COMMAND_HPP
#define SOKOBAN_COMMAND_HPP

#include "../Category.hpp"

#include <SFML/System/Time.hpp>

#include <cassert>
#include <functional>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class Scene_Node;

            struct Command
            {
                Command();
                std::function< void( Scene_Node &, sf::Time ) > action;
                unsigned int _category;
            };

            template< typename Game_Object, typename Function >
                std::function< void( Scene_Node &, sf::Time ) > derived_action( Function fn )
                {
                    return [ = ]( Scene_Node &node, sf::Time dt )
                    {
                        assert( dynamic_cast< Game_Object * >( &node ) != nullptr );
                        fn( static_cast< Game_Object & >( node ), dt );
                    };
                }
        }
    }
}

#endif //SOKOBAN_COMMAND_HPP
