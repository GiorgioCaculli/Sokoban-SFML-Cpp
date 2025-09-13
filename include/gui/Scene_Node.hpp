#ifndef SOKOBAN_SCENE_NODE_HPP
#define SOKOBAN_SCENE_NODE_HPP

#include <ui/Category.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include <vector>
#include <utility>


namespace sokoban::ui::gui
{
    struct Command;
    class Command_Queue;

    class Scene_Node
            : public sf::Transformable
              , public sf::Drawable
    {
    public:
        using Ptr = std::unique_ptr<Scene_Node>;
        using Pair = std::pair<Scene_Node *, Scene_Node *>;

        explicit Scene_Node( Category::Type category = Category::None );

        void attach_child( Ptr child );

        Ptr detach_child( const Scene_Node& node );

        void update( sf::Time dt, Command_Queue& commands );

        sf::Vector2f get_world_positions() const;

        sf::Transform get_world_transform() const;

        void on_command( const Command& command, sf::Time dt ) const;

        virtual unsigned int get_category() const;

        virtual sf::FloatRect get_bounding_rect() const;

        virtual bool is_marked_for_removal() const;

        virtual bool is_destroyed() const;

    private:
        std::vector< Ptr > _children; /** The various children that compose a Scene node */
        Scene_Node* _parent; /** The parent node */
        Category::Type _default_category; /** The default category of each node */
        virtual void update_current( sf::Time dt, Command_Queue& commands );

        void update_children( sf::Time dt, Command_Queue& commands ) const;

        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

        virtual void draw_current( sf::RenderTarget& target, const sf::RenderStates& states ) const;

        void draw_children( sf::RenderTarget& target, const sf::RenderStates& states ) const;

        void draw_bounding_rect( sf::RenderTarget& target, const sf::RenderStates& states ) const;
    };
}


#endif //SOKOBAN_SCENE_NODE_HPP
