#include "board.hpp"

#include <iostream>

using namespace sokoban::core;

Board::Board()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode( 800, 600 ), "Sokoban" );
    window->requestFocus();
    std::string level_lines[] = {
            "    ######\n" ,
            "    ##   #\n" ,
            "    ##$  #\n" ,
            "  ####  $##\n" ,
            "  ##  $ $ #\n" ,
            "#### # ## #   ######\n" ,
            "##   # ## #####  ..#\n" ,
            "## $  $          ..#\n" ,
            "###### ### #@##  ..#\n" ,
            "    ##     #########\n" ,
            "    ########\n"
    };

    for(short i = 0; i < level_lines->length(); i++ )
    {
        level += level_lines[i];
    }

    std::cout << level << std::endl;

    init_board();
}

Board::~Board()
= default;

void Board::init_board()
{
    init_world();
}

void Board::init_world()
{
    walls = new std::vector< Wall * >();
    boxes = new std::vector< Box * >();
    platforms = new std::vector< Platform * >();

    short x = OFFSET;
    short y = OFFSET;

    Wall *wall;
    Box *b;
    Platform *p;

    for( short i = 0; i < level.length(); i++ )
    {
        char item = level[i];

        switch ( item )
        {
        case '\n':
            y += SPACE;
            if( this->w < x )
            {
                this->w = x;
            }
            x = OFFSET;
            break;
        case '#':
            wall = new Wall( x, y );
            walls->push_back( wall );
            x += SPACE;
            break;
        case '$':
            break;
        case '.':
            break;
        case '@':
            break;
        case ' ':
            break;
        default:
            break;
        }
    }
}

short Board::get_board_width()
{
    return w;
}

short Board::get_board_height()
{
    return h;
}

void Board::build_world()
{

}

bool Board::check_wall_collision( Actor* actor, short type )
{
    return false;
}

bool Board::check_box_collision( short type )
{
    return false;
}

void Board::is_completed()
{
    short number_of_boxes = boxes->size();
    short finished_boxes = 0;

    for( short i = 0; i < number_of_boxes; i++ )
    {
        Box box = boxes->at(i);

        for( short j = 0; j < number_of_boxes; j++ )
        {
            Platform platform = platforms->at( j );

            if( box.getX() == platform.getX() && box.getY() == platform.getY() )
            {
                finished_boxes += 1;
            }
        }
    }

    if( finished_boxes == number_of_boxes )
    {
        completed = true;
    }
}

void Board::restart_level()
{
    platforms->clear();
    boxes->clear();
    walls->clear();

    init_world();

    if( completed )
    {
        completed = false;
    }
}
