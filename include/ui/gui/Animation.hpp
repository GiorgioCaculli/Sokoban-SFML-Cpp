#ifndef SOKOBAN_ANIMATION_HPP
#define SOKOBAN_ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>


namespace sokoban::ui::gui
{
    class Animation final
            : public sf::Drawable
              , public sf::Transformable
    {
    public:
        Animation();

        explicit Animation( const sf::Texture& texture );

        void set_texture( const sf::Texture& texture );

        const sf::Texture* get_texture() const;

        void set_frame_size( sf::Vector2i frame_size );

        sf::Vector2i get_frame_size() const;

        void set_num_frames( std::size_t num_frames );

        std::size_t get_num_frames() const;

        void set_repeating( bool flag );

        bool is_repeating() const;

        void restart();

        bool is_finished() const;

        sf::FloatRect get_local_bounds() const;

        sf::FloatRect get_global_bounds() const;

        void update( sf::Time dt );

    private:
        sf::Sprite _sprite; /** The current sprite to display */
        sf::Vector2i _frame_size; /** The sprite's frame size */
        std::size_t _num_frames; /** The number of frames */
        std::size_t _current_frame; /** The current frame */
        sf::Time _duration; /** The duration of the animation */
        sf::Time _elapsed_time; /** The time that went by */
        bool _repeat; /** Whether the animation has to be repeated or not */
        void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
    };
}


#endif //SOKOBAN_ANIMATION_HPP
