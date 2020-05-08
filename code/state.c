#include "global.h"
#include "board.h"
#include "move.h"
#include "comm.h"
#include "client.h"
#include <limits.h>

typedef struct State State;
struct State
{
    State* parent;
    int value;
    int depth;
    // pinakas me pionia? mporei na bgenei apo gamePosition
    // xreiazetai kati pou 8a perigrafei thn katastash
};


// initial state constructoras
State* state()
{
    State *this = malloc( sizeof( State ) );
    this->parent = NULL;
    this->depth = 0;
    this->value = INT_MIN;

    return this;
}

// new state constructor
State* state( State* parent )
{
    State *this = malloc( sizeof( State ) );
    this->parent = parent;
    this->depth = parent->depth + 1;

    return this;
}

void delete_state ( State* this )
{
    free( this );
}


int max_value ( State *this )
{
    if ( terminal_test( this ) == TRUE )
        return utility( this );

    int value = INT_MIN;

    // find each legal action
    // for each action do move and create new state
    // gia ka8e neo state kalese max( v , MIN( neo state ) )
    // epestrepse v tou mikroterou
}

int min_value ( State* this )
{
    if ( terminal_test( this ) == TRUE )
        return utility( this );

    int value = INT_MAX;
}

int terminal_test( State* this )
{

}

int utility( State* this )
{
	int enemy_color = WHITE;
	if ( myColor == WHITE)
		enemy_color = BLACK;

	int my_value = gamePosition.score[ myColor ] ;
}


/** Metraei posa pionia tou sugkekrimenou xrwmatos uparxoun. */
int count_pieces( char color )
{
	int num_pieces = 0;

	for( int i = 0; i < BOARD_ROWS; i++ )
	{
		for( int j = 0; j < BOARD_COLUMNS; j++ )
		{
			if( gamePosition.board[ i ][ j ] == color )
			{
				num_pieces++;
			}
		}
	}
	return num_pieces;
}

/** Elenxei an uparxei dunato pidima */
int jump_possible ( State* this )
{
    int jumpPossible = FALSE;		// determine if we have a jump available
    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if( gamePosition.board[ i ][ j ] == myColor )
            {
                if( canJump( i , j , myColor , &gamePosition ) )
                    jumpPossible = TRUE;
            }
        }
    }
    return jump_possible;
}

void actions()
{

}