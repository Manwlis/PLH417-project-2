#ifndef _STATE_H
#define _STATE_H

#include "global.h"
#include "board.h"
#include "move.h"

#define SEARCH_DEPTH 10
#define A_B_PRUNING_ACTIVE 1
#define MOVE_REORDER_ACTIVE 1
#define NO_STOP_AT_VOLATILE 1
#define MAX_LEGAL_MOVES 25

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

int terminal_test( Position* position , int depth , int jump_flag );

int utility( Position* position , int jump_flag );


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

/** Briskei oles tis dunates kiniseis kai tis bazei ston pinaka legal_moves. Epistrefei to plh8os tous. */
int find_moves_white( Position* position , Move* legal_moves , int jump_flag );
int find_moves_black( Position* position , Move* legal_moves , int jump_flag );

/** Briskei oles tis nees katastaseis apo tis kinhseis sto pinaka move_array. Tis bazei ston pinaka new_positions. */
void do_moves_and_reorder( Position* restrict position , Position* new_positions , Move* move_array , int moves_num , int jump_flag );

/** Metraei posa pionia tou sugkekrimenou xrwmatos uparxoun. */
inline int count_pieces( Position* restrict position , char color )
{
	int num_pieces = 0;

	for( int i = 0; i < BOARD_ROWS; i++ )
		for( int j = 0; j < BOARD_COLUMNS; j++ )
			if( position->board[ i ][ j ] == color )
				num_pieces++;

	return num_pieces;
}

/** Elenxei an uparxei dunato pidima. */
inline int jump_possible ( Position* restrict position )
{
    for( int i = 0; i < BOARD_ROWS; i++ )
        for( int j = 0; j < BOARD_COLUMNS; j++ )
            if( position->board[ i ][ j ] == position->turn ) // autounou pou paizei
                if( canJump( i , j , position->turn , position ) )
                    return TRUE;
    
    return FALSE;
}

/** Epistefei thn kateu8unsh tou paixth pou paizei. +-1 */
inline int player_direction( Position* restrict pos )
{
    if( pos->turn == WHITE )		// find movement's direction
        return 1;
    else
        return -1;
}


// gia to reorder.
inline int heurestic_value( Position* restrict position , int jump_flag )
{
	if ( position->turn = badies_color )
		jump_flag = -jump_flag;
    return position->score[goodies_color] - position->score[badies_color] + position->dead[badies_color] - position->dead[goodies_color] + jump_flag;
}

// gia thn qsort ths reorder
int comparitor( const void * lhs , const void * rhs );

/**********************************************************/
/********************** Data movers ***********************/
/**********************************************************/

/** Copy source Move to target Move. */
inline void copy_move( Move* restrict source , Move* restrict target )
{
	for (int i = 0 ; i < 2 ; i++ )
		for (int j = 0 ; j < MAXIMUM_MOVE_SIZE ; j++ )
			target->tile[i][j] = source->tile[i][j];

	target->color = source->color;	
}

/** Copy source Position to target Position. */
inline void copy_position( Position* restrict source , Position* restrict target )
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