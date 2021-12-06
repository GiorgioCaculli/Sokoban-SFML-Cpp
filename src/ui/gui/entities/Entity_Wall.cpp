#include "Entity_Wall.hpp"

using namespace sokoban::ui::gui::entity;

const float OFFSET = 64;

const std::array< float, 4 > wall_round_beige_asset = {
        0
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > wall_round_black_asset = {
        OFFSET * 1
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > wall_round_brown_asset = {
        OFFSET * 2
        , 0
        , OFFSET
        , OFFSET
};

const std::array< float, 4 > wall_round_white_asset = {
        OFFSET * 3
        , 0
        , OFFSET
        , OFFSET
};

Entity_Wall::Entity_Wall( float x, float y )
        : model::Wall( x, y )
        , Entity( wall_round_white_asset )
{
    _wall_color_map = std::map< Color, std::array< float, 4 > >
            {
                    {   Color::BEIGE, wall_round_beige_asset }
                    , { Color::BLACK, wall_round_black_asset }
                    , { Color::BROWN, wall_round_brown_asset }
                    , { Color::WHITE, wall_round_white_asset }
            };
}

Entity_Wall::Entity_Wall( const Entity_Wall &entity )
: Entity_Wall( entity.get_x(), entity.get_y() )
{
}

Entity_Wall &Entity_Wall::operator=( const Entity_Wall &entity )
{
    if( &entity != this )
    {
        model::Wall::operator=( entity );
        Entity::operator=( entity );
    }
    return *this;
}

Entity_Wall::~Entity_Wall()
{
}

std::string Entity_Wall::to_string() const
{
    return Wall::to_string();
}

const std::map< Entity_Wall::Color, std::array< float, 4>> &Entity_Wall::get_wall_color_map() const
{
    return _wall_color_map;
}

std::ostream &sokoban::ui::gui::entity::operator<<( std::ostream &os, const Entity_Wall &entity )
{
    return os;
}
