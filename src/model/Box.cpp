#include "Box.hpp"

#include <array>
#include <sstream>
#include <iostream>

using namespace sokoban::model;

const float OFFSET = 64;

const std::array< float, 4 > box_beige_light_asset = {
        0
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_black_light_asset = {
        OFFSET * 1
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_blue_light_asset = {
        OFFSET * 2
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_brown_light_asset = {
        OFFSET * 3
        , 0
        , OFFSET
        , OFFSET
}; /** The default asset for the box */
const std::array< float, 4 > box_beige_dark_asset = {
        OFFSET * 4
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_black_dark_asset = {
        OFFSET * 5
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_blue_dark_asset = {
        OFFSET * 6
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_brown_dark_asset = {
        OFFSET * 7
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_white_dark_asset = {
        OFFSET * 8
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_purple_dark_asset = {
        OFFSET * 9
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_red_dark_asset = {
        OFFSET * 10
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_yellow_dark_asset = {
        OFFSET * 11
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_white_light_asset = {
        OFFSET * 12
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_purple_light_asset = {
        OFFSET * 13
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_red_light_asset = {
        OFFSET * 14
        , 0
        , OFFSET
        , OFFSET
};
const std::array< float, 4 > box_yellow_light_asset = {
        OFFSET * 15
        , 0
        , OFFSET
        , OFFSET
};

Box::Box( float x, float y )
        : Movable( x, y, box_brown_light_asset )
{
    _box_color_map = std::map< Color, std::array< float, 4 > >
            {
                    {   Color::BEIGE_LIGHT , box_beige_light_asset }
                    , { Color::BLACK_LIGHT , box_black_light_asset }
                    , { Color::BLUE_LIGHT  , box_blue_light_asset }
                    , { Color::BROWN_LIGHT , box_brown_light_asset }
                    , { Color::BEIGE_DARK  , box_beige_dark_asset }
                    , { Color::BLACK_DARK  , box_black_dark_asset }
                    , { Color::BLUE_DARK   , box_blue_dark_asset }
                    , { Color::BROWN_DARK  , box_brown_dark_asset }
                    , { Color::WHITE_DARK  , box_white_dark_asset }
                    , { Color::PURPLE_DARK , box_purple_dark_asset }
                    , { Color::RED_DARK    , box_red_dark_asset }
                    , { Color::YELLOW_DARK , box_yellow_dark_asset }
                    , { Color::WHITE_LIGHT , box_white_light_asset }
                    , { Color::PURPLE_LIGHT, box_purple_light_asset }
                    , { Color::RED_LIGHT   , box_red_light_asset }
                    , { Color::YELLOW_LIGHT, box_yellow_light_asset }
            };
}

Box::Box( const Box &box )
        : Box( box.get_x(), box.get_y() )
{
}

Box &Box::operator=( const Box &box )
{
    if ( &box != this )
    {
        set_x( box.get_x() );
        set_y( box.get_y() );
        set_asset_coords( box.get_asset_coords() );
    }
    return *this;
}

Box::~Box()
{
    std::cout << "Deletion " << Box::to_string() << std::endl;
}

Actor::ID Box::get_type() const
{
    return Actor::BOX;
}

const std::map< Box::Color, std::array< float, 4 > > &Box::get_box_color_map() const
{
    return _box_color_map;
}

std::string Box::to_string() const
{
    std::stringstream ss;
    ss << "Box: " << Movable::to_string();
    return ss.str();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Box &box )
{
    os << box.to_string();
    return os;
}
