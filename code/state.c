#include "state.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/**********************************************************/
/**************** Constructors/Destructors ****************/
/**********************************************************/

State* root_state( Position* gamePosition , char color )
{
    State *this = malloc( sizeof( State ) );
    this->parent = NULL;
    this->depth = 0;
    this->value = INT_MIN;

    copy_position( gamePosition , &(this->position) );


    return this;
}

State* state( State* parent , Move* move )
{
    State *this = malloc( sizeof( State ) );
    this->parent = parent;
    this->depth = parent->depth + 1;

    copy_position( &(parent->position) , &(this->position) ); // h allagh gurou ginetai sto doMove
    
    copy_move( move , &(this->move) );

    doMove( &(this->position) , &(this->move) );

    return this;
}

void delete_state ( State* this )
{
    free( this );
}


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

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
    // den exei kinish na kanei
    if( !canMove( this , this->position.turn ) )
        return TRUE;
    // isws an den exei mirmigia o antipalos?

    return FALSE;
}

void actions()
{

}

int utility( State* this )
{
	int my_value = this->position.score[ this->position.turn ] ; // isws anti this->position.turn prepei goodies_color
    int enemy_value = this->position.score[ getOtherSide(this->position.turn) ] ;// isws anti this->position.turn prepei badies_color

    return my_value - enemy_value;
}


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

int count_pieces( State* this , char color )
{
	int num_pieces = 0;

	for( int i = 0; i < BOARD_ROWS; i++ )
	{
		for( int j = 0; j < BOARD_COLUMNS; j++ )
		{
			if( this->position.board[ i ][ j ] == color )
			{
				num_pieces++;
			}
		}
	}
	return num_pieces;
}

int jump_possible ( State* this )
{
    int jumpPossible = FALSE;		// determine if we have a jump available

    for( int i = 0; i < BOARD_ROWS; i++ )
        for( int j = 0; j < BOARD_COLUMNS; j++ )
            if( this->position.board[ i ][ j ] == this->position.turn ) // autounou pou paizei
                if( canJump( i , j , this->position.turn , &(this->position) ) )
                    jumpPossible = TRUE;
            
    return jumpPossible;
}


/**********************************************************/
/********************** Data movers ***********************/
/**********************************************************/

void copy_move( Move* source , Move* target )
{
	for (int i = 0 ; i < 2 ; i++ )
		for (int j = 0 ; j < MAXIMUM_MOVE_SIZE ; j++ )
			target->tile[i][j] = source->tile[i][j];

	target->color = source->color;	
}

void copy_position( Position* source , Position* target )
{
	for ( int i = 0 ; i < BOARD_ROWS ; i++ )
		for (int j = 0 ; j < BOARD_COLUMNS ; j++ )
			target->board[i][j] = source->board[i][j];

	target->score[0] = source->score[0];
	target->score[1] = source->score[1];
	target->turn = source->turn;
}