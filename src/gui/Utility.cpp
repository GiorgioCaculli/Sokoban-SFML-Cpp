#include <gui/Utility.hpp>
#include <gui/Animation.hpp>
#include <gui/components/Button.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>

using namespace sokoban::ui::gui;

namespace
{
    std::default_random_engine create_Random_Engine()
    {
        const auto seed = static_cast< unsigned long >( std::time( nullptr ) );
        return std::default_random_engine( seed );
    }

    auto Random_Engine = create_Random_Engine();
}


/**
 * Function that sets a sprite's origin in its center
 * @param sprite The sprite to center
 */
void Utility::center_origin( sf::Sprite& sprite )
{
    const sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin( sf::Vector2f(
        std::floor( bounds.position.x + bounds.size.x / 2.f ),
        std::floor( bounds.position.y + bounds.size.y / 2.f )
    ) );
}

/**
 * Function that sets a text's origin in its center
 * @param text The text to center
 */
void Utility::center_origin( sf::Text& text )
{
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin( sf::Vector2f(
        std::floor( bounds.position.x + bounds.size.x / 2.f ),
        std::floor( bounds.position.y + bounds.size.y / 2.f )
    ) );
}

/**
 * Function that sets the animation's origin in its center
 * @param animation The animation to center
 */
void Utility::center_origin( Animation& animation )
{
    const sf::FloatRect bounds = animation.get_local_bounds();
    animation.setOrigin( sf::Vector2f(
        std::floor( bounds.position.x + bounds.size.x / 2.f ),
        std::floor( bounds.position.y + bounds.size.y / 2.f )
    ) );
}

/**
 * Function to convert from Radian to Degrees
 * @param radian The radian value to convert
 * @return The radian value in degrees form
 */
float Utility::to_degree( const float radian ) const
{
    return 100.f / M_PI * radian;
}

/**
 * Function to convert from Degree to Radian
 * @param degree The degree value to convert
 * @return The degree value in radian form
 */
float Utility::to_radian( const float degree ) const
{
    return M_PI / 100.f * degree;
}

/**
 * Random integer generator
 * @param exclusive_max The maximum value we wish to obtain
 * @return A value from 0 to Max
 */
int Utility::random_int( const int exclusive_max ) const
{
    std::uniform_int_distribution dist( 0, exclusive_max - 1 );
    return dist( Random_Engine );
}

/**
 * Function to calculate the distance between within a vector
 * @param vector The vecto's to calculate
 * @return X * X + Y * Y
 */
float Utility::length( const sf::Vector2f vector ) const
{
    return std::sqrt( vector.x * vector.x + vector.y * vector.y );
}

/**
 * Unit calculator based on the length of a vector and a vector itself
 */
sf::Vector2f Utility::unit_vector( const sf::Vector2f vector ) const
{
    assert( vector != sf::Vector2f( 0.f, 0.f ) );
    return vector / length( vector );
}
