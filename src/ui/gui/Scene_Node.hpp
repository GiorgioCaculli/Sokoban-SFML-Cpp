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
                    : public sf::Transformable,
                            public sf::Drawable,
                            private sf::NonCopyable
            {
            public:
                typedef std::unique_ptr< SceneNode > Ptr;
                SceneNode();
                void attach_child( Ptr child );
                Ptr detach_child( const SceneNode &node );
                void update( sf::Time dt );
                sf::Vector2f get_world_position() const;
                sf::Transform get_world_transform() const;
            private:
                std::vector< Ptr > children;
                SceneNode *parent;
            };
        }
    }
}

#endif //SOKOBAN_SCENE_NODE_HPP
