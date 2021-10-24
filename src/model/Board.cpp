#include "Board.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace sokoban::model;

const int OFFSET = 64;
const int SPACE = 64;

Board::Board( std::string lvl )
: _completed( false )
  , _boxes( std::vector< Box * >() )
  , _walls( std::vector< Wall * >() )
  , _platforms( std::vector< Platform * >() )
  , _player( nullptr )
  , _world( std::vector< Actor * >() )
  , _width( 0 )
  , _height( 0 )
{
    std::string line;
    std::stringstream ss;
    std::ifstream level_file( lvl );
    if( level_file.is_open() )
    {
        while( std::getline( level_file, line ) )
        {
            ss << line << '\n';
        }
        level_file.close();
    }
    _level = std::move( ss.str() );
    init_board();
}

Board::Board( const Board &board )
        : _completed( false )
          , _boxes( std::vector< Box * >() )
          , _walls( std::vector< Wall * >() )
          , _platforms( std::vector< Platform * >() )
          , _player( nullptr )
          , _world( std::vector< Actor * >() )
          , _width( 0 )
          , _height( 0 )
{
    init_board();
}

Board &Board::operator=( const Board &board )
{
    if( &board != this )
    {
        _completed = false;
        _boxes = std::vector< Box * >();
        _walls = std::vector< Wall * >();
        _platforms = std::vector< Platform * >();
        _player = nullptr;
        _world = std::vector< Actor * >();
        _width = 0;
        _height =0;
    }
    init_board();
    return *this;
}

Board::~Board()
{
    for( Wall *wall : _walls )
    {
        delete wall;
    }
    for( Platform *platform : _platforms )
    {
        delete platform;
    }
    for( Box *box : _boxes )
    {
        delete box;
    }
    delete _player;
}

void Board::init_board()
{
    init_world();
}

void Board::init_world()
{
    int x = OFFSET;
    int y = OFFSET;

    Box *box;
    Wall *wall;
    Platform *platform;
    for ( int i = 0; i < _level.length(); i++ )
    {
        char item = _level.at( i );
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

void Board::build_world()
{
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

bool Board::check_wall_collision( Actor *actor, int type )
{
    switch ( type )
    {
    case LEFT_COLLISION:
        for( const Wall *wall : _walls )
        {
            if( actor->is_left_collision( wall ) )
            {
                return true;
            }
        }
        return false;
    case RIGHT_COLLISION:
        for( const Wall *wall : _walls )
        {
            if( actor->is_right_collision( wall ) )
            {
                return true;
            }
        }
        return false;
    case TOP_COLLISION:
        for( const Wall *wall : _walls )
        {
            if( actor->is_top_collision( wall ) )
            {
                return true;
            }
        }
        return false;
    case BOTTOM_COLLISION:
        for( const Wall *wall : _walls )
        {
            if( actor->is_bottom_collision( wall ) )
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

bool Board::check_box_collision( int type )
{
    switch ( type )
    {
    case LEFT_COLLISION:
        for( Box *box : _boxes )
        {
            if( _player->is_left_collision( box ) )
            {
                for( Box *item : _boxes )
                {
                    if( box != item )
                    {
                        if( box->is_left_collision( item ) )
                        {
                            return true;
                        }
                    }
                    if( check_wall_collision( box, LEFT_COLLISION ) )
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
        for( Box *box : _boxes )
        {
            if( _player->is_right_collision( box ) )
            {
                for( Box *item : _boxes )
                {
                    if( box != item )
                    {
                        if( box->is_right_collision( item ) )
                        {
                            return true;
                        }
                    }
                    if( check_wall_collision( box, RIGHT_COLLISION ) )
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
        for( Box *box : _boxes )
        {
            if( _player->is_top_collision( box ) )
            {
                for( Box *item : _boxes )
                {
                    if( box != item )
                    {
                        if( box->is_top_collision( item ) )
                        {
                            return true;
                        }
                    }
                    if( check_wall_collision( box, TOP_COLLISION ) )
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
        for( Box *box : _boxes )
        {
            if( _player->is_bottom_collision( box ) )
            {
                for( Box *item : _boxes )
                {
                    if( box != item )
                    {
                        if( box->is_bottom_collision( item ) )
                        {
                            return true;
                        }
                    }
                    if( check_wall_collision( box, BOTTOM_COLLISION ) )
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

int Board::get_board_width() const
{
    return _width;
}

int Board::get_board_height() const
{
    return _height;
}

bool Board::is_completed() const
{
    return _completed;
}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Board &board )
{
    os << board._level;
    /* os << "_boxes: " << _board._boxes << " _walls: " << _board._walls << " _platforms: " << _board._platforms << " _player: " << _board._player << " width: " << _board.width << " _height: " << _board._height;*/
    return os;
}

std::vector< Actor * > Board::get_world()
{
    return _world;
}
