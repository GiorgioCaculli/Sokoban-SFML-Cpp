#include <ui/gui/Animation.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sokoban::ui::gui;

/**
 * Default constructor for the animation
 */
Animation::Animation()
    : Animation( sf::Texture() )
{
}

/**
 * Default constructor for the animation based on a specific texture
 * @param texture The texture to initialize
 */
Animation::Animation( const sf::Texture& texture )
    : _sprite( texture )
      , _num_frames( 0 )
      , _current_frame( 0 )
      , _duration( sf::Time::Zero )
      , _elapsed_time( sf::Time::Zero )
      , _repeat( false )
{
}

/**
 * Setter for the animation's texture
 * @param texture The new texture to set
 */
void Animation::set_texture( const sf::Texture& texture )
{
    _sprite.setTexture( texture );
}

/**
 * Getter for the current active texture
 * @return The texture that is displayed
 */
const sf::Texture* Animation::get_texture() const
{
    return &_sprite.getTexture();
}

/**
 * Setter for the current frame size
 * @param frame_size The new frame size
 */
void Animation::set_frame_size( const sf::Vector2i frame_size )
{
    _frame_size = frame_size;
}

/**
 * Getter for the frame size
 * @return The current frame size
 */
sf::Vector2i Animation::get_frame_size() const
{
    return _frame_size;
}

/**
 * Setter for the number of frames
 * @param num_frames The new number of frames
 */
void Animation::set_num_frames( const std::size_t num_frames )
{
    _num_frames = num_frames;
}

/**
 * Getter for the number of frames
 * @return The number of frames
 */
std::size_t Animation::get_num_frames() const
{
    return _num_frames;
}

/**
 * Setter that defines whether the animation loops or not
 * @param flag Whether the animation loops or not
 */
void Animation::set_repeating( const bool flag )
{
    _repeat = flag;
}

/**
 * Getter that retrieves whether the animation loops or not
 * @return whether the animation loops or not
 */
bool Animation::is_repeating() const
{
    return _repeat;
}

/**
 * Make the animation restart from the very first frame
 */
void Animation::restart()
{
    _current_frame = 0;
}

/**
 * Function that checks whether an animation has ended or not
 * @return Whether an animation has ended or not
 */
bool Animation::is_finished() const
{
    return _current_frame >= _num_frames;
}

/**
 * Getter for the maximum bounds of an animation
 * @return The maximum bounds of an animation
 */
sf::FloatRect Animation::get_local_bounds() const
{
    return { getOrigin(), static_cast< sf::Vector2f >( get_frame_size() ) };
}

/**
 * The globally accessible bounds
 * @return The globally accessible bounds
 */
sf::FloatRect Animation::get_global_bounds() const
{
    return getTransform().transformRect( get_local_bounds() );
}

/**
 * Realtime update each frame of the animation
 * @param dt The clock time
 */
void Animation::update( const sf::Time dt )
{
    const sf::Time time_per_frame = _duration / static_cast< float >( _num_frames );
    _elapsed_time += dt;

    const sf::Vector2i texture_bounds( _sprite.getTexture().getSize() );
    sf::IntRect texture_rect = _sprite.getTextureRect();

    if ( _current_frame == 0 )
    {
        texture_rect = sf::IntRect( sf::Vector2i( 0, 0 ), sf::Vector2i( _frame_size.x, _frame_size.y ) );
    }
    while ( _elapsed_time >= time_per_frame && ( _current_frame <= _num_frames || _repeat ) )
    {
        texture_rect.position.x += texture_rect.size.x;

        if ( texture_rect.position.x + texture_rect.size.x > texture_bounds.x )
        {
            texture_rect.position.x = 0;
            texture_rect.position.y += texture_rect.size.y;
        }

        _elapsed_time += time_per_frame;

        if ( _repeat )
        {
            _current_frame = ( _current_frame + 1 ) % _num_frames;
            if ( _current_frame == 0 )
            {
                texture_rect = sf::IntRect( sf::Vector2i( 0, 0 ), sf::Vector2i( _frame_size.x, _frame_size.y ) );
            } else
            {
                _current_frame++;
            }
        }
    }
    _sprite.setTextureRect( texture_rect );
}

/**
 * Visually display the various frames of an animation
 */
void Animation::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( _sprite, states );
}
