#ifndef SOKOBAN_SCENE_NODE_HPP
#define SOKOBAN_SCENE_NODE_HPP

#include "../Category.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include <vector>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            struct Command;

            class Scene_Node
                    : public sf::Transformable
                      , public sf::Drawable
                      , private sf::NonCopyable
            {
            public:
                typedef std::unique_ptr< Scene_Node > Ptr;
                Scene_Node();
                void attach_child( Ptr child );
                Ptr detach_child( const Scene_Node &node );
                void update( sf::Time dt );
                sf::Vector2f get_world_positions() const;
                sf::Transform get_world_transform() const;
                void on_command( const Command &command, sf::Time dt );
                virtual unsigned int get_category() const;
            private:
                std::vector< Ptr > _children;
                Scene_Node *_parent;
                virtual void update_current( sf::Time dt );
                void update_children( sf::Time dt );
                virtual void draw( sf::RenderTarget &target, sf::RenderStates states ) const;
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
                void draw_children( sf::RenderTarget &target, sf::RenderStates states ) const;
            };
        }
    }
}

#endif //SOKOBAN_SCENE_NODE_HPP
