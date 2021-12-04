#ifndef SOKOBAN_SCENE_NODE_HPP
#define SOKOBAN_SCENE_NODE_HPP

#include "../Category.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <set>
#include <memory>
#include <vector>
#include <utility>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            struct Command;
            class Command_Queue;

            class Scene_Node
                    : public sf::Transformable
                      , public sf::Drawable
                      , private sf::NonCopyable
            {
            public:
                typedef std::unique_ptr< Scene_Node > Ptr;
                typedef std::pair< Scene_Node *, Scene_Node * > Pair;
                explicit Scene_Node( Category::Type category = Category::None );
                void attach_child( Ptr child );
                Ptr detach_child( const Scene_Node &node );
                void update( sf::Time dt, Command_Queue &commands );
                sf::Vector2f get_world_positions() const;
                sf::Transform get_world_transform() const;
                void on_command( const Command &command, sf::Time dt );
                virtual unsigned int get_category() const;
                virtual sf::FloatRect get_bounding_rect() const;
                virtual bool is_marked_for_removal() const;
                virtual bool is_destroyed() const;
            private:
                std::vector< Ptr > _children;
                Scene_Node *_parent;
                Category::Type _default_category;
                virtual void update_current( sf::Time dt, Command_Queue &commands );
                void update_children( sf::Time dt, Command_Queue &commands );
                void draw( sf::RenderTarget &target, sf::RenderStates states ) const override;
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
                void draw_children( sf::RenderTarget &target, sf::RenderStates states ) const;
                void draw_bounding_rect( sf::RenderTarget &target, sf::RenderStates states ) const;
            };
        }
    }
}

#endif //SOKOBAN_SCENE_NODE_HPP
