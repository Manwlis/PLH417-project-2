#ifndef _STATE_H
#define _STATE_H

#include "global.h"
#include "board.h"
#include "move.h"

/** Ws state, 8ewrw ena stigmaiothpo tou board meta apo ka8e kinish.
 * Den xreiazomai parapanw plhroforia apo to Position, gia auto den uparxei struct state.
 * Gia na dhmiourgh8ei nea katastash (neo Position) ginetai pass by value.
 */

char goodies_color;
char badies_color;


int flag_grammh;
int flag_teleiwse;
int flag_parathse;
/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move );

int max_value ( Position position , int depth );

int min_value ( Position position , int depth );

int terminal_test( Position* position , int depth );

int utility( Position* position );


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

/** doMove Wrapper. Epistrefei to neo best_move_value. */
int call_max( Position* position , Move* temp_move , int depth , int best_move_value );

/** doMove Wrapper. Epistrefei to neo best_move_value. */
int call_min( Position* position , Move* temp_move , int depth , int best_move_value );

/** Metraei posa pionia tou sugkekrimenou xrwmatos uparxoun. */
int count_pieces( Position* position , char color );

/** Elenxei an uparxei dunato pidima. */
int jump_possible ( Position* position );


/**********************************************************/
/********************** Data movers ***********************/
/**********************************************************/

/** Copy source Move to target Move. */
void copy_move( Move* source , Move* target );

/** Copy source Position to target Position. */
void copy_position( Position* source , Position* target );

/** Epistefei thn kateu8unsh tou paixth pou paizei. +-1 */
int player_direction( Position* pos );
#endif