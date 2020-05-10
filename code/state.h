#ifndef _STATE_H
#define _STATE_H

#include "global.h"
#include "board.h"
#include "move.h"

typedef struct 
{
    State* parent;
    int value;
    int depth;

    Position position;  // exei board, score kai pios paizei
    Move move;          // exei pinaka kinishs

    // xreiazetai kati pou 8a perigrafei thn katastash?
}State;


char goodies_color;
char badies_color;

/**********************************************************/
/**************** Constructors/Destructors ****************/
/**********************************************************/

/** Root State constructor.
 * Returns a pointer of the new state.
 */
State* root_state( Position* gamePosition , char color );

/** New State constructor.
 * Returns a pointer of the new state.
 */
State* state( State* parent , Move* move );

void delete_state ( State* this );


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

int max_value ( State* this );

int min_value ( State* this );

int terminal_test( State* this );

void actions();

int utility( State* this );


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

/** Metraei posa pionia tou sugkekrimenou xrwmatos uparxoun. */
int count_pieces( State* this , char color );

/** Elenxei an uparxei dunato pidima. */
int jump_possible ( State* this );


/**********************************************************/
/********************** Data movers ***********************/
/**********************************************************/

/** Copy source Move to target Move. */
void copy_move( Move* source , Move* target );

/** Copy source Position to target Position. */
void copy_position( Position* source , Position* target );

#endif