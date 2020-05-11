#include "state.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move )
{
    // loop me oles tis dinates kiniseis
    // an nea kinish exei kalutero value: move = new_move 
}

int max_value ( Position position )
{
    if ( terminal_test( &position ) == TRUE )
        return utility( &position );

    int value = INT_MIN;

    Move newMove;
    Position newPosition;

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        newMove.tile[ 0 ][ 0 ] = -1;		//null move

        // neo state
        copy_position( &position , &newPosition );
        doMove( &newPosition , &newMove );

        // epilogh megaluterou value apo ta nea state
        int child_value = min_value( newPosition ) ;
        if( child_value > value )
            return value;
    }
    else //uparxei kinish
    {
        // elenxos pidimatos
        int jump = jump_possible( &position );            

        for( int i = 0; i < BOARD_ROWS; i++ )
        {
            for( int j = 0; j < BOARD_COLUMNS; j++ )
            {
                //piece we are going to move
                newMove.tile[ 0 ][ 0 ] = i;
                newMove.tile[ 1 ][ 0 ] = j;

                // uparxei pidima
                if ( jump == FALSE )
                {
                    // kane ka8e kinish kai epestrepse to kalutero skor. Den xreiazetai na 8umamai ti htan h kinhsh.
                }
                // den uparxei
                else
                {
                    
                }
                
            }
        }
    }
}

int min_value ( Position position )
{
    if ( terminal_test( &position ) == TRUE )
        return utility( &position );

    int value = INT_MAX;
}

int terminal_test( Position* position )
{
    // isws an den exei mirmigia kapios?
    // an ola ta mirmigia mou einai pera apo tou allou

    return FALSE;
}

int utility( Position* position )
{
	int my_value = position->score[ position->turn ] ; // isws anti this->position.turn prepei goodies_color
    int enemy_value = position->score[ getOtherSide( position->turn ) ] ;// isws anti this->position.turn prepei badies_color

    return my_value - enemy_value;
}


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

int count_pieces( Position* position , char color )
{
	int num_pieces = 0;

	for( int i = 0; i < BOARD_ROWS; i++ )
		for( int j = 0; j < BOARD_COLUMNS; j++ )
			if( position->board[ i ][ j ] == color )
				num_pieces++;

	return num_pieces;
}

int jump_possible ( Position* position )
{
    int jumpPossible = FALSE;		// determine if we have a jump available

    for( int i = 0; i < BOARD_ROWS; i++ )
        for( int j = 0; j < BOARD_COLUMNS; j++ )
            if( position->board[ i ][ j ] == position->turn ) // autounou pou paizei
                if( canJump( i , j , position->turn , &position ) )
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