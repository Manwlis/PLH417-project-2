#include "state.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move )
{
    int legal_moves = 0;
    // elenxos pidimatos
    int jump_flag = jump_possible( position );

    int column_direction = player_direction( position );
    
    int value;
    int best_move_value = INT_MIN;

    Position new_position;
    Move temp_move;
    temp_move.color = position->turn;

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if( position->board[ i ][ j ] == position->turn ) // diko tou pioni
            {
                //piece we are going to move
                temp_move.tile[ 0 ][ 0 ] = i;
                temp_move.tile[ 1 ][ 0 ] = j;

                if ( jump_flag == FALSE )
                {
/******** jump not possible ********/
                    // kane ka8e kinish kai epestrepse to kalutero skor. Den xreiazetai na 8umamai ti htan h kinhsh.
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * column_direction ;
                    temp_move.tile[ 0 ][ 2 ] = -1; // mia kinish an den uparxei pidima

                    // kinish aristera
                    temp_move.tile[ 1 ][ 1 ] = j - 1;
                    if( isLegal( position , &temp_move ))
                    {
legal_moves++;
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
legal_moves++;
                        copy_position( position , &new_position );
                        doMove2( &new_position , &temp_move );

                        value = min_value( new_position );
                        if( best_move_value < value )
                        {
                            best_move_value = value;
                            copy_move( &temp_move , move );
                        }
                    }
/***********************************/           
                }
                else if ( canJump( i , j , position->turn , position ) )
                {
/******** Jump possible ********/ // dokimazw xwris can jump
                    temp_move.tile[0][1] = temp_move.tile[0][0] + 2 * column_direction;
                    for ( int row_direction1 = -2 ; row_direction1 <= 2 ; row_direction1 += 4)
                    {
                        temp_move.tile[1][1] = temp_move.tile[1][0] + row_direction1;
                        temp_move.tile[0][2] = -1;
                        printf("( %d , %d ) , ( %d , %d ) , ( %d ) , %d\n" , temp_move.tile[0][0] , temp_move.tile[1][0] , temp_move.tile[0][1] , temp_move.tile[1][1] , temp_move.tile[0][2] ,  isLegal( position , &temp_move ));
                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                        {
legal_moves++;
                            copy_position( position , &new_position );
                            doMove2( &new_position , &temp_move );

                            value = min_value( new_position );
                            if( best_move_value < value )
                            {
                                best_move_value = value;
                                copy_move( &temp_move , move );
                            }
                        }
                        else // exei kai allo
                        {
                            temp_move.tile[0][2] = temp_move.tile[ 0 ][ 1 ] + 2 * column_direction;
                            for ( int row_direction2 = -2 ; row_direction2 <= 2 ; row_direction2 += 4)
                            {
                                temp_move.tile[1][2] = temp_move.tile[1][1] + row_direction2;
                                temp_move.tile[0][3] = -1;
                                if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                                {
legal_moves++;
                                    copy_position( position , &new_position );
                                    doMove2( &new_position , &temp_move );

                                    value = min_value( new_position );
                                    if( best_move_value < value )
                                    {
                                        best_move_value = value;
                                        copy_move( &temp_move , move );
                                    }
                                }
                                else
                                {
                                    temp_move.tile[0][3] = temp_move.tile[ 0 ][ 2 ] + 2 * column_direction;
                                    for ( int row_direction3 = -2 ; row_direction3 <= 2 ; row_direction3 += 4)
                                    {
                                        temp_move.tile[1][3] = temp_move.tile[1][2] + row_direction3;
                                        temp_move.tile[0][4] = -1;
                                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                                        {
legal_moves++;
                                            copy_position( position , &new_position );
                                            doMove2( &new_position , &temp_move );

                                            value = min_value( new_position );
                                            if( best_move_value < value )
                                            {
                                                best_move_value = value;
                                                copy_move( &temp_move , move );
                                            }
                                        }
                                        else
                                        {
                                            temp_move.tile[0][4] = temp_move.tile[ 0 ][ 3 ] + 2 * column_direction;
                                            for ( int row_direction4 = -2 ; row_direction4 <= 2 ; row_direction4 += 4)
                                            {
                                                temp_move.tile[1][4] = temp_move.tile[1][3] + row_direction4;
                                                temp_move.tile[0][5] = -1;
                                                if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                                                {
legal_moves++;
                                                    copy_position( position , &new_position );
                                                    doMove2( &new_position , &temp_move );

                                                    value = min_value( new_position );
                                                    if( best_move_value < value )
                                                    {
                                                        best_move_value = value;
                                                        copy_move( &temp_move , move );
                                                    }
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
legal_moves++;
                                                            copy_position( position , &new_position );
                                                            doMove2( &new_position , &temp_move );

                                                            value = min_value( new_position );
                                                            if( best_move_value < value )
                                                            {
                                                                best_move_value = value;
                                                                copy_move( &temp_move , move );
                                                            }
                                                        }
                                                    } // 5 jump
                                                }
                                            } // 4 jump
                                        }
                                    } // 3 jump
                                }
                            } // 2 jump
                        }
                    } // 1 jump
/******************************/
                }
            }
        }
    }
    printf( "Legal moves: %d\n" , legal_moves );
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

    int column_direction = player_direction( &position );          

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if( position.board[ i ][ j ] == position.turn ) // diko tou pioni
            {
                //piece we are going to move
                temp_move.tile[ 0 ][ 0 ] = i;
                temp_move.tile[ 1 ][ 0 ] = j;

                // den uparxei pidima
                if ( jump_flag == FALSE )
                {
                    // kane ka8e kinish kai epestrepse to kalutero skor. Den xreiazetai na 8umamai ti htan h kinhsh.
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * column_direction;
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
                else if ( canJump( i , j , position.turn , &position ) )
                {
/******** Jump possible ********/ // dokimazw xwris can jump
                    temp_move.tile[0][1] = temp_move.tile[0][0] + 2 * column_direction;
                    for ( int row_direction1 = -2 ; row_direction1 <= 2 ; row_direction1 += 4)
                    {
                        temp_move.tile[1][1] = temp_move.tile[1][0] + row_direction1;
                        temp_move.tile[0][2] = -1;
                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                        {
                            copy_position( &position , &new_position );
                            doMove2( &new_position , &temp_move );

                            value = min_value( new_position );
                            if( best_move_value < value )
                                best_move_value = value;
                        }
                        else // exei kai allo
                        {
                            temp_move.tile[0][2] = temp_move.tile[ 0 ][ 1 ] + 2 * column_direction;
                            for ( int row_direction2 = -2 ; row_direction2 <= 2 ; row_direction2 += 4)
                            {
                                temp_move.tile[1][2] = temp_move.tile[1][1] + row_direction2;
                                temp_move.tile[0][3] = -1;
                                if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                {
                                    copy_position( &position , &new_position );
                                    doMove2( &new_position , &temp_move );

                                    value = min_value( new_position );
                                    if( best_move_value < value )
                                        best_move_value = value;
                                }
                                else
                                {
                                    temp_move.tile[0][3] = temp_move.tile[ 0 ][ 2 ] + 2 * column_direction;
                                    for ( int row_direction3 = -2 ; row_direction3 <= 2 ; row_direction3 += 4)
                                    {
                                        temp_move.tile[1][3] = temp_move.tile[1][2] + row_direction3;
                                        temp_move.tile[0][4] = -1;
                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                        {
                                            copy_position( &position , &new_position );
                                            doMove2( &new_position , &temp_move );

                                            value = min_value( new_position );
                                            if( best_move_value < value )
                                                best_move_value = value;
                                        }
                                        else
                                        {
                                            temp_move.tile[0][4] = temp_move.tile[ 0 ][ 3 ] + 2 * column_direction;
                                            for ( int row_direction4 = -2 ; row_direction4 <= 2 ; row_direction4 += 4)
                                            {
                                                temp_move.tile[1][4] = temp_move.tile[1][3] + row_direction4;
                                                temp_move.tile[0][5] = -1;
                                                if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                {
                                                    copy_position( &position , &new_position );
                                                    doMove2( &new_position , &temp_move );

                                                    value = min_value( new_position );
                                                    if( best_move_value < value )
                                                        best_move_value = value;
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            copy_position( &position , &new_position );
                                                            doMove2( &new_position , &temp_move );

                                                            value = min_value( new_position );
                                                            if( best_move_value < value )
                                                                best_move_value = value;
                                                        }
                                                    } // 5 jump
                                                }
                                            } // 4 jump
                                        }
                                    } // 3 jump
                                }
                            } // 2 jump
                        }
                    } // 1 jump
/******************************/   
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

    int column_direction = player_direction( &position );          

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
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * column_direction ;
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
                else if ( canJump( i , j , position.turn , &position ) )
                {
/******** Jump possible ********/ // dokimazw xwris can jump
                    temp_move.tile[0][1] = temp_move.tile[0][0] + 2 * column_direction;
                    for ( int row_direction1 = -2 ; row_direction1 <= 2 ; row_direction1 += 4)
                    {
                        temp_move.tile[1][1] = temp_move.tile[1][0] + row_direction1;
                        temp_move.tile[0][2] = -1;
                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                        {
                            copy_position( &position , &new_position );
                            doMove2( &new_position , &temp_move );

                            value = max_value( new_position );
                            if( best_move_value > value )
                                best_move_value = value;
                        }
                        else // exei kai allo
                        {
                            temp_move.tile[0][2] = temp_move.tile[ 0 ][ 1 ] + 2 * column_direction;
                            for ( int row_direction2 = -2 ; row_direction2 <= 2 ; row_direction2 += 4)
                            {
                                temp_move.tile[1][2] = temp_move.tile[1][1] + row_direction2;
                                temp_move.tile[0][3] = -1;
                                if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                {
                                    copy_position( &position , &new_position );
                                    doMove2( &new_position , &temp_move );

                                    value = max_value( new_position );
                                    if( best_move_value > value )
                                        best_move_value = value;
                                }
                                else
                                {
                                    temp_move.tile[0][3] = temp_move.tile[ 0 ][ 2 ] + 2 * column_direction;
                                    for ( int row_direction3 = -2 ; row_direction3 <= 2 ; row_direction3 += 4)
                                    {
                                        temp_move.tile[1][3] = temp_move.tile[1][2] + row_direction3;
                                        temp_move.tile[0][4] = -1;
                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                        {
                                            copy_position( &position , &new_position );
                                            doMove2( &new_position , &temp_move );

                                            value = max_value( new_position );
                                            if( best_move_value > value )
                                                best_move_value = value;
                                        }
                                        else
                                        {
                                            temp_move.tile[0][4] = temp_move.tile[ 0 ][ 3 ] + 2 * column_direction;
                                            for ( int row_direction4 = -2 ; row_direction4 <= 2 ; row_direction4 += 4)
                                            {
                                                temp_move.tile[1][4] = temp_move.tile[1][3] + row_direction4;
                                                temp_move.tile[0][5] = -1;
                                                if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                {
                                                    copy_position( &position , &new_position );
                                                    doMove2( &new_position , &temp_move );

                                                    value = max_value( new_position );
                                                    if( best_move_value > value )
                                                        best_move_value = value;
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            copy_position( &position , &new_position );
                                                            doMove2( &new_position , &temp_move );

                                                            value = max_value( new_position );
                                                            if( best_move_value > value )
                                                                best_move_value = value;
                                                        }
                                                    } // 5 jump
                                                }
                                            } // 4 jump
                                        }
                                    } // 3 jump
                                }
                            } // 2 jump
                        }
                    } // 1 jump
/******************************/   
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
	int my_value = position->score[ goodies_color ] * 2;
    int enemy_value = position->score[ badies_color ] * 2;

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
    for( int i = 0; i < BOARD_ROWS; i++ )
        for( int j = 0; j < BOARD_COLUMNS; j++ )
            if( position->board[ i ][ j ] == position->turn ) // autounou pou paizei
                if( canJump( i , j , position->turn , position ) )
                    return TRUE;
            
    return FALSE;
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