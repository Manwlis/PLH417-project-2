#ifndef _STATE_H
#define _STATE_H

#include "global.h"
#include "board.h"
#include "move.h"

// ba8os 7
// a-b pruning: 81,637 , 27,615
// xwris pruning: 3,554,855 , 362,742   // ~ 8.8^7. Logiko na exei peripou 9 kiniseis dia8esimes

// ba8os 9
// a-b pruning: 600,745 , 175,223
// apagoreutiko     // 8.8^9 ~= 316,478,381 

// ba8os 10
// a-b pruning: 1,896,083 , 4,631,834 / 2.602.140 , 5.735.550

#define SEARCH_DEPTH 8
#define A_B_PRUNING_ACTIVE 1
#define MAX_LEGAL_MOVES 30
/** Ws state, 8ewrw ena stigmaiothpo tou board meta apo ka8e kinish.
 * Den xreiazomai parapanw plhroforia apo to Position, gia auto den uparxei struct state.
 * Gia na dhmiourgh8ei nea katastash (neo Position) ginetai pass by value.
 */

char goodies_color;
char badies_color;

int num_moves;
int min_num;
int max_num;

/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move );

int max_value ( Position position , int depth , int a , int b );

int min_value ( Position position , int depth , int a , int b  );

int terminal_test( Position* position , int depth );

int utility( Position* position );


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

/** Briskei oles tis dunates kiniseis kai tis bazei ston pinaka legal_moves. Epistrefei to plh8os tous. */
int find_moves( Position* position , Move* legal_moves );

/** Metraei posa pionia tou sugkekrimenou xrwmatos uparxoun. */
inline int count_pieces( Position* position , char color )
{
	int num_pieces = 0;

	for( int i = 0; i < BOARD_ROWS; i++ )
		for( int j = 0; j < BOARD_COLUMNS; j++ )
			if( position->board[ i ][ j ] == color )
				num_pieces++;

	return num_pieces;
}

/** Elenxei an uparxei dunato pidima. */
inline int jump_possible ( Position* position )
{
    for( int i = 0; i < BOARD_ROWS; i++ )
        for( int j = 0; j < BOARD_COLUMNS; j++ )
            if( position->board[ i ][ j ] == position->turn ) // autounou pou paizei
                if( canJump( i , j , position->turn , position ) )
                    return TRUE;
    
    return FALSE;
}

/** Epistefei thn kateu8unsh tou paixth pou paizei. +-1 */
inline int player_direction( Position* pos )
{
    if( pos->turn == WHITE )		// find movement's direction
        return 1;
    else
        return -1;
}

/**********************************************************/
/********************** Data movers ***********************/
/**********************************************************/

/** Copy source Move to target Move. */
inline void copy_move( Move* source , Move* target )
{
	for (int i = 0 ; i < 2 ; i++ )
		for (int j = 0 ; j < MAXIMUM_MOVE_SIZE ; j++ )
			target->tile[i][j] = source->tile[i][j];

	target->color = source->color;	
}

/** Copy source Position to target Position. */
inline void copy_position( Position* source , Position* target )
{
	for ( int i = 0 ; i < BOARD_ROWS ; i++ )
		for (int j = 0 ; j < BOARD_COLUMNS ; j++ )
			target->board[i][j] = source->board[i][j];

	target->score[0] = source->score[0];
	target->score[1] = source->score[1];
	target->turn = source->turn;

    target->dead[0] = source->dead[0];
    target->dead[1] = source->dead[1];
}

#endif