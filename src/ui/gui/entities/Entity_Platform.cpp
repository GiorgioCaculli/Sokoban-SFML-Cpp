#include <ui/gui//entities/Entity_Platform.hpp>

using namespace sokoban::ui::gui::entity;

constexpr float OFFSET = 32;

const std::array< float, 4 > platform_beige_asset = {
    0, 0, OFFSET, OFFSET
};

const std::array< float, 4 > platform_black_asset = {
    OFFSET * 1, 0, OFFSET, OFFSET
};

const std::array< float, 4 > platform_blue_asset = {
    OFFSET * 2, 0, OFFSET, OFFSET
};

const std::array< float, 4 > platform_brown_asset = {
    OFFSET * 3, 0, OFFSET, OFFSET
};

const std::array< float, 4 > platform_white_asset = {
    OFFSET * 4, 0, OFFSET, OFFSET
};

const std::array< float, 4 > platform_purple_asset = {
    OFFSET * 5, 0, OFFSET, OFFSET
};

const std::array< float, 4 > platform_red_asset = {
    OFFSET * 6, 0, OFFSET, OFFSET
};

const std::array< float, 4 > platform_yellow_asset = {
    OFFSET * 7, 0, OFFSET, OFFSET
};

/**
 * Default Entity Platform constructor
 * @param x The coordinates on the X axis
 * @param y The coordinates on the Y axis
 */
Entity_Platform::Entity_Platform( float x, float y )
    : Platform( x, y )
      , Entity( platform_blue_asset )
{
    _platform_color_map = std::map< Color, std::array< float, 4 > >
    {
        { Color::BEIGE, platform_beige_asset }, { Color::BLACK, platform_black_asset },
        { Color::BLUE, platform_blue_asset }, { Color::BROWN, platform_brown_asset },
        { Color::WHITE, platform_white_asset }, { Color::PURPLE, platform_purple_asset },
        { Color::RED, platform_red_asset }, { Color::YELLOW, platform_yellow_asset }
    };
}

/**
 * The copy constructor for the Entity Platform
 * @param entity The Platform we wish to copy the information from
 */
Entity_Platform::Entity_Platform( const Entity_Platform& entity )
    : Entity_Platform( entity.get_x(), entity.get_y() )
{
}

/**
 * Redefinition of the = operator
 * @param entity The entity we wish to copy the information from
 * @return The entity with the copied platform's information
 */
Entity_Platform& Entity_Platform::operator=( const Entity_Platform& entity )
{
    if ( &entity != this )
    {
        Platform::operator=( entity );
        Entity::operator=( entity );
    }
    return *this;
}

/**
 * Default constructor for the Platform entity
 */
Entity_Platform::~Entity_Platform()
= default;

/**
 * Textual output containing the platform's information
 * @return The textual output with the platform's information
 */
std::string Entity_Platform::to_string() const
{
    return Platform::to_string();
}

/**
 * Getter for the mapper containing the asset's coordinates based on the color
 * @return The mapper containing the coordinates based on the color
 */
const std::map< Entity_Platform::Color, std::array< float, 4 > >& Entity_Platform::get_platform_color_map() const
{
    return _platform_color_map;
}
