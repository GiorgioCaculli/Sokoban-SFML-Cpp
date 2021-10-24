#ifndef SOKOBAN_SCENE_NODE_HPP
#define SOKOBAN_SCENE_NODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>

namespace sokoban
{
    namespace ui
    {
        namespace gui
        {
            class SceneNode
                    : public sf::Transformable
                      , public sf::Drawable
                      , private sf::NonCopyable
            {
            public:
                SceneNode();
                virtual ~SceneNode();
                void attach_child( SceneNode *child );
                SceneNode *detach_child( const SceneNode *node );
                void update( sf::Time dt );
                sf::Vector2f get_world_position() const;
                sf::Transform get_world_transform() const;
            private:
                std::vector< SceneNode * > *_children;
                SceneNode *_parent;
                virtual void update_current( const sf::Time &dt );
                void update_children( const sf::Time &dt );
                virtual void draw( sf::RenderTarget &target, sf::RenderStates states ) const;
                virtual void draw_current( sf::RenderTarget &target, sf::RenderStates states ) const;
                void draw_children( sf::RenderTarget &target, sf::RenderStates &states ) const;
            };
        }
    }
}

#endif //SOKOBAN_SCENE_NODE_HPP
