#include "Animation.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sokoban::ui::gui;

Animation::Animation()
: _sprite()
, _frame_size()
, _num_frames( 0 )
, _current_frame( 0 )
, _duration( sf::Time::Zero )
, _elapsed_time( sf::Time::Zero )
, _repeat( false )
{
}

Animation::Animation( const sf::Texture &texture )
: _sprite( texture )
, _frame_size()
, _num_frames( 0 )
, _current_frame( 0 )
, _duration( sf::Time::Zero )
, _elapsed_time( sf::Time::Zero )
, _repeat( false )
{
}

void Animation::set_texture( const sf::Texture &texture )
{
    _sprite.setTexture( texture );
}

const sf::Texture *Animation::get_texture() const
{
    return _sprite.getTexture();
}

void Animation::set_frame_size( sf::Vector2i frame_size )
{
    _frame_size = frame_size;
}

sf::Vector2i Animation::get_frame_size() const
{
    return _frame_size;
}

void Animation::set_num_frames( std::size_t num_frames )
{
    _num_frames = num_frames;
}

std::size_t Animation::get_num_frames() const
{
    return _num_frames;
}

void Animation::set_repeating( bool flag )
{
    _repeat = flag;
}

bool Animation::is_repeating() const
{
    return _repeat;
}

void Animation::restart()
{
    _current_frame = 0;
}

bool Animation::is_finished() const
{
    return _current_frame >= _num_frames;
}

sf::FloatRect Animation::get_local_bounds() const
{
    return sf::FloatRect( getOrigin(), static_cast< sf::Vector2f >( get_frame_size() ) );
}

sf::FloatRect Animation::get_global_bounds() const
{
    return getTransform().transformRect( get_local_bounds() );
}

void Animation::update( sf::Time dt )
{
    sf::Time time_per_frame = _duration / static_cast< float >( _num_frames );
    _elapsed_time += dt;

    sf::Vector2i texture_bounds( _sprite.getTexture()->getSize() );
    sf::IntRect texture_rect = _sprite.getTextureRect();

    if( _current_frame == 0 )
    {
        texture_rect = sf::IntRect( 0, 0, _frame_size.x, _frame_size.y );
    }
    while( _elapsed_time >= time_per_frame && ( _current_frame <= _num_frames || _repeat ) )
    {
        texture_rect.left += texture_rect.width;

        if( texture_rect.left + texture_rect.width > texture_bounds.x )
        {
            texture_rect.left = 0;
            texture_rect.top += texture_rect.height;
        }

        _elapsed_time += time_per_frame;

        if( _repeat )
        {
            _current_frame = ( _current_frame + 1 ) % _num_frames;
            if( _current_frame == 0 )
            {
                texture_rect = sf::IntRect( 0, 0, _frame_size.x, _frame_size.y );
            }
            else
            {
                _current_frame++;
            }
        }
    }
    _sprite.setTextureRect( texture_rect );
}

void Animation::draw( sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( _sprite, states );
}
