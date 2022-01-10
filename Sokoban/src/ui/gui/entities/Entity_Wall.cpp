#include <gzc/games/sokoban/ui/gui/sfml/entities/Entity_Wall.hpp>

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

/**
 * Default constructor for the Wall Entity
 * @param x The coordinates on the X axis
 * @param y The coordinates on the Y axis
 */
Entity_Wall::Entity_Wall( float x, float y )
        : core::Wall( x, y )
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

/**
 * Copy constructor for the Wall entity
 * @param entity The entity we wish to copy the information from
 */
Entity_Wall::Entity_Wall( const Entity_Wall &entity )
: Entity_Wall( entity.get_x(), entity.get_y() )
{
}

/**
 * Redefinition of the = operator
 * @param entity The entity we wish to copy the information from
 * @return The new entity with the copied information
 */
Entity_Wall &Entity_Wall::operator=( const Entity_Wall &entity )
{
    if( &entity != this )
    {
        core::Wall::operator=( entity );
        Entity::operator=( entity );
    }
    return *this;
}

/**
 * Default destructor for the Wall entity
 */
Entity_Wall::~Entity_Wall()
= default;

/**
 * Textual output of the Wall entity
 * @return Textual output containing the Wall's information
 */
std::string Entity_Wall::to_string() const
{
    return Wall::to_string();
}

/**
 * Getter for the mapper containing the coordinates of the assets based on each color
 * @return The mapper containing the coordinates of the assets based on each color
 */
const std::map< Entity_Wall::Color, std::array< float, 4>> &Entity_Wall::get_wall_color_map() const
{
    return _wall_color_map;
}
