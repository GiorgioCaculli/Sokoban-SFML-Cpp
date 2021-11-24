#include "Platform.hpp"

#include <array>
#include <sstream>
#include <iostream>

using namespace sokoban::model;

const float OFFSET = 32;

const std::array< float, 4 > platform_beige_asset = {
        0
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > platform_black_asset = {
        OFFSET * 1
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > platform_blue_asset = {
        OFFSET * 2
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > platform_brown_asset = {
        OFFSET * 3
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > platform_white_asset = {
        OFFSET * 4
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > platform_purple_asset = {
        OFFSET * 5
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > platform_red_asset = {
        OFFSET * 6
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > platform_yellow_asset = {
        OFFSET * 7
        , 0
        , OFFSET
        , OFFSET
};

Platform::Platform( float x, float y )
        : Actor( x, y, platform_purple_asset )
{
    _platform_color_map = std::map< Color, std::array< float, 4 > >
            {
                    {   Color::BEIGE , platform_beige_asset }
                    , { Color::BLACK , platform_black_asset }
                    , { Color::BLUE  , platform_blue_asset }
                    , { Color::BROWN , platform_brown_asset }
                    , { Color::WHITE , platform_white_asset }
                    , { Color::PURPLE, platform_purple_asset }
                    , { Color::RED   , platform_red_asset }
                    , { Color::YELLOW, platform_yellow_asset }
            };
}

Platform::Platform( const Platform &platform )
        : Platform( platform.get_x(), platform.get_y() )
{
}

Platform &Platform::operator=( const Platform &platform )
{
    if ( &platform != this )
    {
        set_x( platform.get_x() );
        set_y( platform.get_y() );
        set_asset_coords( platform.get_asset_coords() );
    }
    return *this;
}

Platform::~Platform()
{
    std::cout << "Deletion " << Platform::to_string() << std::endl;
}

Actor::ID Platform::get_type() const
{
    return Actor::PLATFORM;
}

const std::map< Platform::Color, std::array< float, 4 > > &Platform::get_platform_color_map() const
{
    return _platform_color_map;
}

std::string Platform::to_string() const
{
    std::stringstream ss;
    ss << "Platform: " << Actor::to_string();
    return ss.str();
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Platform &platform )
{
    os << platform.to_string();
    return os;
}
