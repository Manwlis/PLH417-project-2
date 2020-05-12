#include "state.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move )
{
    // elenxos pidimatos
    int jump_flag = jump_possible( position );

    int direction = player_direction( position );
    
    int value;
    int best_move_value = INT_MIN;

    Position new_position;
    Move temp_move;
    temp_move.color = position->turn;

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if( position->board[ i ][ j ] == goodies_color ) // diko tou pioni
            {
                //piece we are going to move
                temp_move.tile[ 0 ][ 0 ] = i;
                temp_move.tile[ 1 ][ 0 ] = j;

                // den uparxei pidima
                if ( jump_flag == FALSE )
                {
                    // kane ka8e kinish kai epestrepse to kalutero skor. Den xreiazetai na 8umamai ti htan h kinhsh.
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * direction;
                    temp_move.tile[ 0 ][ 2 ] = -1; // mia kinish an den uparxei pidima

                    // kinish aristera
                    temp_move.tile[ 1 ][ 1 ] = j - 1;
                    if( isLegal( position , &temp_move ))
                    {
                        // kanei kinish
                        copy_position( position , &new_position );
                        doMove2( &new_position , &temp_move );

                        // thn krataei an einai h kaluterh mexri stigmhs
                        value = min_value( new_position );

                        if( best_move_value < value )
                        {
                            best_move_value = value;
                            copy_move( &temp_move , move );
                        }
                    }

                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( position , &temp_move ))
                    {
                        copy_position( position , &new_position );
                        doMove2( &new_position , &temp_move );

                        value = min_value( new_position );
                        if( best_move_value < value )
                        {
                            best_move_value = value;
                            copy_move( &temp_move , move );
                        }
                    }
                
                }
                // uparxei
                else
                {
                    
                }
            }
        }
    }
}

// se periptwsh stack overflow na pernaw pointer, malloc kainourgio struct, copy se auto
int max_value ( Position position )
{
    if ( terminal_test( &position ) == TRUE )
        return utility( &position );

    Move temp_move;
    Position new_position;

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        temp_move.tile[ 0 ][ 0 ] = -1;		//null move

        // neo state
        copy_position( &position , &new_position );
        doMove2( &new_position , &temp_move );

        // Den exei kinish, den xreiazetai na epileksei apo kapou
        return min_value( new_position ) ;
    }

    //uparxei kinish
    int value;
    int best_move_value = INT_MIN;

    // elenxos pidimatos
    int jump_flag = jump_possible( &position );

    int direction = player_direction( &position );          

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if( position.board[ i ][ j ] == goodies_color ) // diko tou pioni
            {
                //piece we are going to move
                temp_move.tile[ 0 ][ 0 ] = i;
                temp_move.tile[ 1 ][ 0 ] = j;

                // den uparxei pidima
                if ( jump_flag == FALSE )
                {
                    // kane ka8e kinish kai epestrepse to kalutero skor. Den xreiazetai na 8umamai ti htan h kinhsh.
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * direction;
                    temp_move.tile[ 0 ][ 2 ] = -1; // mia kinish an den uparxei pidima

                    // kinish aristera
                    temp_move.tile[ 1 ][ 1 ] = j - 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        // kanei kinish
                        copy_position( &position , &new_position );
                        doMove2( &new_position , &temp_move );

                        // thn krataei an einai h kaluterh mexri stigmhs
                        value = min_value( new_position );
                        if( best_move_value < value )
                            best_move_value = value;
                    }

                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        copy_position( &position , &new_position );
                        doMove2( &new_position , &temp_move );

                        value = min_value( new_position );
                        if( best_move_value < value )
                            best_move_value = value;
                    }
                }
                // uparxei
                else
                {
                    
                }
            }
        }
    }
    return best_move_value;
}

/* Idia ilopoihsh me to max_value, me monh diafora best_value = INT_MAX kai psaxnw mikrotero */
int min_value ( Position position )
{
    if ( terminal_test( &position ) == TRUE )
        return utility( &position );

    Move temp_move;
    Position new_position;

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        temp_move.tile[ 0 ][ 0 ] = -1;		//null move

        // neo state
        copy_position( &position , &new_position );
        doMove2( &new_position , &temp_move );

        // Den exei kinish, den xreiazetai na epileksei apo kapou
        return max_value( new_position ) ;
    }

    //uparxei kinish
    int value;
    int best_move_value = INT_MAX;

    // elenxos pidimatos
    int jump_flag = jump_possible( &position );

    int direction = player_direction( &position );          

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if( position.board[ i ][ j ] == badies_color ) // diko tou pioni
                {
                //piece we are going to move
                temp_move.tile[ 0 ][ 0 ] = i;
                temp_move.tile[ 1 ][ 0 ] = j;

                // den uparxei pidima
                if ( jump_flag == FALSE )
                {
                    // kane ka8e kinish kai epestrepse to kalutero skor. Den xreiazetai na 8umamai ti htan h kinhsh.
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * direction;
                    temp_move.tile[ 0 ][ 2 ] = -1; // mia kinish an den uparxei pidima

                    // kinish aristera
                    temp_move.tile[ 1 ][ 1 ] = j - 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        // kanei kinish
                        copy_position( &position , &new_position );
                        doMove2( &new_position , &temp_move );

                        // thn krataei an einai h kaluterh mexri stigmhs
                        value = max_value( new_position );
                        if( best_move_value > value )
                            best_move_value = value;
                    }

                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        copy_position( &position , &new_position );
                        doMove2( &new_position , &temp_move );

                        value = max_value( new_position );
                        if( best_move_value > value )
                            best_move_value = value;
                    }
                }
                // uparxei
                else
                {
                    
                }
            }
        }
    }
    return best_move_value;
}

int terminal_test( Position* position )
{
    // isws an den exei mirmigia kapios?
    // an ola ta mirmigia mou einai pera apo tou allou
    int ants[2] = { 0 , 0 };
    int food = 0;

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if ( position->board[i][j] == WHITE )
                ants[0]++;
            else if ( position->board[i][j] == BLACK )
                ants[1]++;
            else if ( position->board[i][j] == RTILE )
                food++;
        }
    }

    // Den exei mirmigia => Den mporei na beltiwsei allo to value.
    if( ants[ position->turn ] == 0 )
        return TRUE;

    // O antipalos den exei mirmigia kai den uparxei fai => Den mporei na allaksei to value.
    if( ants[ getOtherSide( position->turn ) ] == 0 && food == 0 )
        return TRUE;

    // Den mporei na kerdisei akoma kai an ola pane teleia.
    int best_score_change = ants[ position->turn ] + food;
    if( position->score[ position->turn ] + best_score_change < position->score[ getOtherSide( position->turn ) ] )
        return TRUE;

    // Den mporei na xasei akoma kai an ola pane xalia
    int worst_score_change = ants[ getOtherSide( position->turn ) ] + food;
    if( position->score[ getOtherSide( position->turn ) ] + worst_score_change < position->score[ position->turn ] )
        return TRUE;

    return FALSE;
}

int utility( Position* position )
{
	int my_value = position->score[ goodies_color ];
    int enemy_value = position->score[ badies_color ];

    int ants[2] = { 0 , 0 };
    int food = 0;

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if ( position->board[i][j] == WHITE )
                ants[0]++;
            else if ( position->board[i][j] == BLACK )
                ants[1]++;
            else if ( position->board[i][j] == RTILE )
                food++;
        }
    }
    my_value += ants[ goodies_color ];
    enemy_value += ants[ badies_color ];

    // to fai an einai sto board den exei value, an to xw faei 8a dwsei 1, an to xei faei o ex8ros 8a dwsei -1.
    // Etsi to parotrinw na to faei kai na empodisei ton ex8ro na to faei. Epishs den iperektimw thn aksia tou.

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
                if( canJump( i , j , position->turn , position ) )
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

int player_direction( Position* pos )
{
    if( pos->turn == WHITE )		// find movement's direction
        return 1;
    else
        return -1;
}
// mporoun na ginoun polla inline