#include "Board.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace sokoban::model;

const int OFFSET = 64; /** Variable used for the amount of pixels an actor can move */
const int SPACE = 64; /** Variable used for the size of each character */

/**
 * Constructor for the board
 * The parameter lvl is meant to be a string containing the path to a text file
 * That text file will contain the skeleton of the level, meaning that from the
 * symbols present on the text file, we can build every actor of the game.
 * # represents a wall
 * @ represents the player
 * . represents a platform
 * $ represents a box
 * An empty space is just emptiness
 * @param lvl The path for the level
 */
Board::Board( const std::string &lvl )
        : _boxes()
          , _walls()
          , _platforms()
          , _player( nullptr )
          , _world()
          , _width( 0 )
          , _height( 0 )
{
    std::string line;
    std::stringstream ss;
    std::ifstream level_file( lvl );
    if ( level_file.is_open() )
    {
        while ( std::getline( level_file, line ) )
        {
            ss << line << '\n';
        }
        level_file.close();
    }
    _level = std::move( ss.str() );
    init_board();
}

/**
 * Copy constructor of the board
 * Primarily used to create a backup of the board.
 * An example of usage for this constructor could be to load a board when
 * the player hits the reset button
 * @param board The board from which we wish to create a copy
 */
Board::Board( const Board &board )
        : Board( board._level )
{
}

/**
 * Redefinition of the = operator
 * Same usage as the copy constructor
 * @param board
 * @return
 */
Board &Board::operator=( const Board &board )
{
    if ( &board != this )
    {
        _level = board._level;
        _boxes = board._boxes;
        _walls = board._walls;
        _platforms = board._platforms;
        _player = board._player;
        _world = board._world;
        _width = board._width;
        _height = board._height;
    }
    init_board();
    return *this;
}

/**
 * Board's destructor
 * Meant to clear the memory from any actor that has been initialised
 */
Board::~Board()
{
    for ( Wall *wall: _walls )
    {
        delete wall;
    }
    for ( Platform *platform: _platforms )
    {
        delete platform;
    }
    for ( Box *box: _boxes )
    {
        delete box;
    }
    delete _player;
    _boxes.clear();
    _walls.clear();
    _platforms.clear();
    _world.clear();
}

/**
 * Executions before the world initialization
 */
void Board::init_board()
{
    init_world();
}

/**
 * World initialization
 * Meant to initialise every actor on the board
 * As stated in the constructor:
 * * # represents a wall
 * @ represents the player
 * . represents a platform
 * $ represents a box
 * An empty space is just emptiness
 * Each actor is inserted into its respective vector
 */
void Board::init_world()
{
    _boxes = std::vector< Box * >();
    _walls = std::vector< Wall * >();
    _platforms = std::vector< Platform * >();
    float x = OFFSET;
    float y = OFFSET;

    Box *box;
    Wall *wall;
    Platform *platform;
    for ( char item: _level )
    {
        switch ( item )
        {
            case '\n':
                y += SPACE;
                if ( _width < x )
                {
                    _width = x;
                }
                x = OFFSET;
                break;
            case '#':
                wall = new Wall( x, y );
                _walls.insert( _walls.begin(), wall );
                x += SPACE;
                break;
            case '$':
                box = new Box( x, y );
                _boxes.insert( _boxes.begin(), box );
                x += SPACE;
                break;
            case '.':
                platform = new Platform( x, y );
                _platforms.insert( _platforms.begin(), platform );
                x += SPACE;
                break;
            case '@':
                _player = new Player( x, y );
                x += SPACE;
                break;
            case '*':
                box = new Box( x, y );
                platform = new Platform( x, y );
                _boxes.insert( _boxes.begin(), box );
                _platforms.insert( _platforms.begin(), platform );
                x += SPACE;
                break;
            case '+':
                _player = new Player( x, y );
                platform = new Platform( x, y );
                _platforms.insert( _platforms.begin(), platform );
                x += SPACE;
                break;
            case ' ':
                x += SPACE;
                break;
            default:
                break;
        }
        _height = y;
    }
    build_world();
}

/**
 * Definition of each actor in their respective category.
 * This will allow is to easily clear out their memory simultaneously
 */
void Board::build_world()
{
    _world = std::vector< Actor * >();
    for ( Wall *wall: _walls )
    {
        _world.insert( _world.begin(), wall );
    }
    for ( Platform *platform: _platforms )
    {
        _world.insert( _world.begin(), platform );
    }
    for ( Box *box: _boxes )
    {
        _world.insert( _world.begin(), box );
    }
    _world.insert( _world.begin(), _player );
}

/**
 * Function to check whether there is a collision between an actor and a wall
 * @param actor The actor causing the collision
 * @param type The type of collision: TOP, BOTTOM, LEFT, RIGHT
 * @return true if a collision took place, false if not
 */
bool Board::check_wall_collision( Actor *actor, int type )
{
    switch ( type )
    {
        case LEFT_COLLISION:
            for ( const Wall *wall: _walls )
            {
                if ( actor->is_left_collision( wall ) )
                {
                    return true;
                }
            }
            return false;
        case RIGHT_COLLISION:
            for ( const Wall *wall: _walls )
            {
                if ( actor->is_right_collision( wall ) )
                {
                    return true;
                }
            }
            return false;
        case TOP_COLLISION:
            for ( const Wall *wall: _walls )
            {
                if ( actor->is_top_collision( wall ) )
                {
                    return true;
                }
            }
            return false;
        case BOTTOM_COLLISION:
            for ( const Wall *wall: _walls )
            {
                if ( actor->is_bottom_collision( wall ) )
                {
                    return true;
                }
            }
            return false;
        default:
            break;
    }
    return false;
}

/**
 * Functions that checks whether there is a collision between an actor and a box
 * @param type The type of collision: TOP, BOTTOM, LEFT, RIGHT
 * @return true if a collision took place, false if not
 */
bool Board::check_box_collision( int type )
{
    switch ( type )
    {
        case LEFT_COLLISION:
            for ( Box *box: _boxes )
            {
                if ( _player->is_left_collision( box ) )
                {
                    for ( Box *item: _boxes )
                    {
                        if ( box != item )
                        {
                            if ( box->is_left_collision( item ) )
                            {
                                return true;
                            }
                        }
                        if ( check_wall_collision( box, LEFT_COLLISION ) )
                        {
                            return true;
                        }
                    }
                    box->move( -SPACE, 0 );
                    is_completed();
                }
            }
            return false;
        case RIGHT_COLLISION:
            for ( Box *box: _boxes )
            {
                if ( _player->is_right_collision( box ) )
                {
                    for ( Box *item: _boxes )
                    {
                        if ( box != item )
                        {
                            if ( box->is_right_collision( item ) )
                            {
                                return true;
                            }
                        }
                        if ( check_wall_collision( box, RIGHT_COLLISION ) )
                        {
                            return true;
                        }
                    }
                    box->move( SPACE, 0 );
                    is_completed();
                }
            }
            return false;
        case TOP_COLLISION:
            for ( Box *box: _boxes )
            {
                if ( _player->is_top_collision( box ) )
                {
                    for ( Box *item: _boxes )
                    {
                        if ( box != item )
                        {
                            if ( box->is_top_collision( item ) )
                            {
                                return true;
                            }
                        }
                        if ( check_wall_collision( box, TOP_COLLISION ) )
                        {
                            return true;
                        }
                    }
                    box->move( 0, -SPACE );
                    is_completed();
                }
            }
            return false;
        case BOTTOM_COLLISION:
            for ( Box *box: _boxes )
            {
                if ( _player->is_bottom_collision( box ) )
                {
                    for ( Box *item: _boxes )
                    {
                        if ( box != item )
                        {
                            if ( box->is_bottom_collision( item ) )
                            {
                                return true;
                            }
                        }
                        if ( check_wall_collision( box, BOTTOM_COLLISION ) )
                        {
                            return true;
                        }
                    }
                    box->move( 0, SPACE );
                    is_completed();
                }
            }
            return false;
        default:
            break;
    }
    return false;
}

/**
 * Getter for the board width
 * @return The width of the board
 */
float Board::get_board_width() const
{
    return _width;
}

/**
 * Getter for the board height
 * @return The height of the board
 */
float Board::get_board_height() const
{
    return _height;
}

/**
 * Function that allows the played to know whether the level is completed
 * @return True if all the boxes are on the platforms
 */
bool Board::is_completed() const
{
    unsigned long number_of_boxes = _boxes.size();
    int finished_boxes = 0;

    for ( Box *box: _boxes )
    {
        for ( Platform *platform: _platforms )
        {
            if ( box->get_x() == platform->get_x() && box->get_y() == platform->get_y() )
            {
                finished_boxes += 1;
            }
        }
    }

    if ( finished_boxes == number_of_boxes )
    {
        return true;
    }

    return false;
}

/**
 * Redefinition of the << operator
 * Meant to be used when outputting the board textually
 * @param os The base output stream
 * @param board The board to output
 * @return Textual output of the various actor's positions
 */
std::ostream &sokoban::model::operator<<( std::ostream &os, const Board &board )
{
    os << board._level;
    for ( Actor *actor: board._world )
    {
        std::cout << *actor << std::endl;
    }
    return os;
}

/**
 * Function to retrieve all the actors on the board
 * @return The vector containing the various actors
 */
std::vector< Actor * > Board::get_world()
{
    return _world;
}
