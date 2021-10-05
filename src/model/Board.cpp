#include "Board.hpp"

#include <string>
#include <sstream>
#include <iostream>

using namespace sokoban::model;

const int OFFSET = 30;
const int SPACE = 20;
std::string level;

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
    for ( Box *boxe: *boxes )
    {
        delete boxe;
    }
    delete boxes;

    for ( Wall *wall: *walls )
    {
        delete wall;
    }
    delete walls;

    for ( Platform *platform: *platforms )
    {
        delete platform;
    }
    delete platforms;

    delete player;
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
    }
}

void Board::build_world()
{

}

bool Board::check_wall_collision( Actor *actor, int type )
{
    return false;
}

bool Board::check_bag_collision( int type )
{
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

void Board::is_completed() const
{

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
