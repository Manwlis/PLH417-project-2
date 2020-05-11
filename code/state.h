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


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move );

int max_value ( Position position );

int min_value ( Position position );

int terminal_test( Position* position );

int utility( Position* position );


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

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

#endif