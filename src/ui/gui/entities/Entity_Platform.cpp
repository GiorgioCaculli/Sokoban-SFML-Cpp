#include "Entity_Platform.hpp"

using namespace sokoban::ui::gui::entity;

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

Entity_Platform::Entity_Platform( float x, float y )
: Platform( x, y )
, Entity( platform_blue_asset )
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

Entity_Platform::Entity_Platform( const Entity_Platform &entity )
: Entity_Platform( entity.get_x(), entity.get_y() )
{
}

Entity_Platform &Entity_Platform::operator=( const Entity_Platform &entity )
{
    if( &entity != this )
    {
        model::Platform::operator=( entity );
        Entity::operator=( entity );
    }
    return *this;
}

Entity_Platform::~Entity_Platform()
{
    model::Platform::~Platform();
}

std::string Entity_Platform::to_string() const
{
    return model::Platform::to_string();
}

const std::map< Entity_Platform::Color, std::array< float, 4>> &Entity_Platform::get_platform_color_map() const
{
    return _platform_color_map;
}

std::ostream &sokoban::ui::gui::entity::operator<<( std::ostream &os, const Entity_Platform &entity )
{
    os << entity.to_string();
    return os;
}
