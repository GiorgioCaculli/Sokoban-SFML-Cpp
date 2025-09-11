#include <ui/gui/entities/Entity_Box.hpp>

using namespace sokoban::ui::gui::entity;
using namespace gzc::sokoban::core;


/**
 * Constructor for the entity box
 * @param x The position on the X axis
 * @param y The position on the Y axis
 */
Entity_Box::Entity_Box( const float x, const float y )
    : Box( x, y )
{
    constexpr float SPRITE_SHEET_PLACEMENT_Y_COORDINATE = 0;

    /* TODO: Apply FOR loop + mapping for cleaner generation, need to overcome the single naming issue (mapping) */
    const std::array box_beige_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 0, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_black_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 1, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_blue_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 2, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_brown_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 3, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    }; /** The default asset for the box */
    const std::array box_beige_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 4, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_black_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 5, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_blue_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 6, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_brown_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 7, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_white_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 8, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_purple_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 9, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_red_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 10, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_yellow_dark_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 11, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_white_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 12, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_purple_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 13, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_red_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 14, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    const std::array box_yellow_light_asset = {
        SPRITE_SHEET_SPRITE_OFFSET * 15, SPRITE_SHEET_PLACEMENT_Y_COORDINATE, SPRITE_SHEET_SPRITE_OFFSET, SPRITE_SHEET_SPRITE_OFFSET
    };
    _box_color_map = std::map< Color, std::array< float, 4 > >
    {
        { Color::BEIGE_LIGHT, box_beige_light_asset }, { Color::BLACK_LIGHT, box_black_light_asset },
        { Color::BLUE_LIGHT, box_blue_light_asset }, { Color::BROWN_LIGHT, box_brown_light_asset },
        { Color::BEIGE_DARK, box_beige_dark_asset }, { Color::BLACK_DARK, box_black_dark_asset },
        { Color::BLUE_DARK, box_blue_dark_asset }, { Color::BROWN_DARK, box_brown_dark_asset },
        { Color::WHITE_DARK, box_white_dark_asset }, { Color::PURPLE_DARK, box_purple_dark_asset },
        { Color::RED_DARK, box_red_dark_asset }, { Color::YELLOW_DARK, box_yellow_dark_asset },
        { Color::WHITE_LIGHT, box_white_light_asset }, { Color::PURPLE_LIGHT, box_purple_light_asset },
        { Color::RED_LIGHT, box_red_light_asset }, { Color::YELLOW_LIGHT, box_yellow_light_asset }
    };
}

/**
 * Copy constructor of a box entity
 */
Entity_Box::Entity_Box( const Entity_Box& box )
    : Entity_Box( box.get_x(), box.get_y() )
{
}

/**
 * Redefinition of the = operator
 * @param box The box we wish to copy the information from
 * @return The new box with the copied box's information
 */
Entity_Box& Entity_Box::operator=( const Entity_Box& box )
{
    if ( &box != this )
    {
        set_asset_coordinates( box.get_asset_coordinates() );
    }
    return *this;
}

/**
 * Based destructor for the box entity
 */
Entity_Box::~Entity_Box()
= default;

/**
 * Getter meant to retrieve the actor's nature
 */
Actor::ID Entity_Box::get_type() const
{
    return BOX;
}

/**
 * Textual format of the box's information
 * @return The Box Entity's information in textual format
 */
std::string Entity_Box::to_string() const
{
    return Box::to_string();
}

/**
 * Getter for the mapper containing the various coordinates of the box based on the color
 * @return The color's mapper
 */
const std::map< Entity_Box::Color, std::array< float, 4 > >& Entity_Box::get_box_color_map() const
{
    return _box_color_map;
}
