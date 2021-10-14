#include "Board.hpp"

#include <string>
#include <sstream>
#include <iostream>

using namespace sokoban::model;

const int OFFSET = 64;
const int SPACE = 64;
std::string level;

Board::Board( std::string lvl )
{
    level = std::move( lvl );
    init_board();
    completed = false;
}

Board::Board()
{
    std::stringstream ss;
    ss << "    ######\n";
    ss << "    ##   #\n";
    ss << "    ##$  #\n";
    ss << "  ####  $##\n";
    ss << "  ##  $ $ #\n";
    ss << "#### # ## #   ######\n";
    ss << "##   # ## #####  ..#\n";
    ss << "## $  $          ..#\n";
    ss << "###### ### #@##  ..#\n";
    ss << "    ##     #########\n";
    ss << "    ########\n";
    level = ss.str();
    init_board();
    completed = false;
}

Board::Board( const Board &board )
        : boxes( board.boxes )
          , walls( board.walls )
          , platforms( board.platforms )
          , player( board.player )
{

}

Board::~Board()
{
    for ( Actor *actor: *world )
    {
        delete actor;
    }

    delete world;
}

void Board::init_board()
{
    init_world();
}

void Board::init_world()
{
    boxes = new std::vector< Box * >();
    walls = new std::vector< Wall * >();
    platforms = new std::vector< Platform * >();
    int x = OFFSET;
    int y = OFFSET;

    Box *box;
    Wall *wall;
    Platform *platform;
    for ( int i = 0; i < level.length(); i++ )
    {
        char item = level.at( i );
        switch ( item )
        {
        case '\n':
            y += SPACE;
            if ( width < x )
            {
                width = x;
            }
            x = OFFSET;
            break;
        case '#':
            wall = new Wall( x, y );
            walls->insert( walls->begin(), wall );
            x += SPACE;
            break;
        case '$':
            box = new Box( x, y );
            boxes->insert( boxes->begin(), box );
            x += SPACE;
            break;
        case '.':
            platform = new Platform( x, y );
            platforms->insert( platforms->begin(), platform );
            x += SPACE;
            break;
        case '@':
            player = new Player( x, y );
            x += SPACE;
            break;
        case ' ':
            x += SPACE;
            break;
        default:
            break;
        }
        height = y;
    }
    build_world();
}

void Board::build_world()
{
    world = new std::vector< Actor * >();
    for ( Wall *wall: *walls )
    {
        world->insert( world->begin(), wall );
    }
    for ( Platform *platform: *platforms )
    {
        world->insert( world->begin(), platform );
    }
    for ( Box *box: *boxes )
    {
        world->insert( world->begin(), box );
    }
    world->insert( world->begin(), player );
}

bool Board::check_wall_collision( Actor *actor, int type )
{
    switch ( type )
    {
    case LEFT_COLLISION:
        for( const Wall *wall : *walls )
        {
            if( actor->is_left_collision( wall ) )
            {
                return true;
            }
        }
        return false;
    case RIGHT_COLLISION:
        for( const Wall *wall : *walls )
        {
            if( actor->is_right_collision( wall ) )
            {
                return true;
            }
        }
        return false;
    case TOP_COLLISION:
        for( const Wall *wall : *walls )
        {
            if( actor->is_top_collision( wall ) )
            {
                return true;
            }
        }
        return false;
    case BOTTOM_COLLISION:
        for( const Wall *wall : *walls )
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
        for( Box *box : *boxes )
        {
            if( player->is_left_collision( box ) )
            {
                for( Box *item : *boxes )
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
        for( Box *box : *boxes )
        {
            if( player->is_right_collision( box ) )
            {
                for( Box *item : *boxes )
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
        for( Box *box : *boxes )
        {
            if( player->is_top_collision( box ) )
            {
                for( Box *item : *boxes )
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
        for( Box *box : *boxes )
        {
            if( player->is_bottom_collision( box ) )
            {
                for( Box *item : *boxes )
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
    return width;
}

int Board::get_board_height() const
{
    return height;
}

bool Board::is_completed() const
{
    return completed;
}

void Board::restart_level() const
{

}

std::ostream &sokoban::model::operator<<( std::ostream &os, const Board &board )
{
    os << level;
    /* os << "boxes: " << board.boxes << " walls: " << board.walls << " platforms: " << board.platforms << " player: " << board.player << " width: " << board.width << " height: " << board.height;*/
    return os;
}

std::vector< Actor * > *Board::get_world()
{
    return world;
}
