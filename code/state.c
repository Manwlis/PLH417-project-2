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
                        
                        value = call_min( position , &temp_move , 0 , best_move_value );
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
                    
                        value = call_min( position , &temp_move , 0 , best_move_value );
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
                        
                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                        {

                            value = call_min( position , &temp_move , 0 , best_move_value );
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
                                    
                                    value = call_min( position , &temp_move , 0 , best_move_value );
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
                                            
                                            value = call_min( position , &temp_move , 0 , best_move_value );
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
                                                    value = call_min( position , &temp_move , 0 , best_move_value );
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
                                                            value = call_min( position , &temp_move , 0 , best_move_value );
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
}


// se periptwsh stack overflow na pernaw pointer, malloc kainourgio struct, copy se auto
int max_value ( Position position , int depth )
{
    depth++;
//max_num++;
    if ( terminal_test( &position , depth ) == TRUE )
    {
//termatika++;
//printf("min: %d , depth: %d , value: %d \n", min_num , depth , utility( &position ) );
        return utility( &position );
    }
    Move temp_move;
    temp_move.color = position.turn;
    Position new_position;

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        return call_min( &position , &temp_move , depth , INT_MIN );
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
                        best_move_value = call_min( &position , &temp_move , depth , best_move_value );
                    }

                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        best_move_value = call_min( &position , &temp_move , depth , best_move_value );
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
                            best_move_value = call_min( &position , &temp_move , depth , best_move_value );
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
                                    best_move_value = call_min( &position , &temp_move , depth , best_move_value );
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
                                            best_move_value = call_min( &position , &temp_move , depth , best_move_value );
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
                                                    best_move_value = call_min( &position , &temp_move , depth , best_move_value );
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            best_move_value = call_min( &position , &temp_move , depth , best_move_value );
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
int min_value ( Position position , int depth )
{
    depth++;
//min_num++;
    if ( terminal_test( &position , depth ) == TRUE )
    {
//termatika++;
//printf("min: %d , depth: %d , value: %d \n", min_num , depth , utility( &position ) );
        return utility( &position );
    }
    Move temp_move;
    temp_move.color = position.turn;
    Position new_position;

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        return call_max( &position , &temp_move , depth , INT_MAX );
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
                        best_move_value = call_max( &position , &temp_move , depth , best_move_value );
                    }

                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        best_move_value = call_max( &position , &temp_move , depth , best_move_value );
                    }
                }
                else if ( canJump( i , j , position.turn , &position ) )
                {
/******** Jump possible ********/
                    temp_move.tile[0][1] = temp_move.tile[0][0] + 2 * column_direction;
                    for ( int row_direction1 = -2 ; row_direction1 <= 2 ; row_direction1 += 4)
                    {
                        temp_move.tile[1][1] = temp_move.tile[1][0] + row_direction1;
                        temp_move.tile[0][2] = -1;
                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                        {
                            best_move_value = call_max( &position , &temp_move , depth , best_move_value );
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
                                    best_move_value = call_max( &position , &temp_move , depth , best_move_value );
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
                                            best_move_value = call_max( &position , &temp_move , depth , best_move_value );
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
                                                    best_move_value = call_max( &position , &temp_move , depth , best_move_value );
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            best_move_value = call_max( &position , &temp_move , depth , best_move_value );
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

flag_grammh = FALSE;
flag_teleiwse = FALSE;
flag_parathse = FALSE;

int terminal_test( Position* position , int depth )
{
    if ( depth == 7 )
        return TRUE;
    // isws an den exei mirmigia kapios?
    // an ola ta mirmigia mou einai pera apo tou allou
    int ants[2] = { 0 , 0 };
    int food = 0;

    int upsulotero_grammh_aspro = -1;
    int xamhloterh_grammh_mauro = 12;

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

            if ( position->board[i][j] == BLACK )
                xamhloterh_grammh_mauro = i; // telutaio mauro
            else if ( position->board[i][j] == WHITE && upsulotero_grammh_aspro == -1 )
                upsulotero_grammh_aspro = i; // prwto aspro
        }
    }

    // den uparxei fai kai den mporei na ginei kapia aixmalwsia.
    if (upsulotero_grammh_aspro > xamhloterh_grammh_mauro && food == 0 )
    {
        if(depth == 1 && flag_grammh == FALSE )
        {
            flag_grammh = TRUE;
            printf("grammes!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf(" %d , %d\n" , upsulotero_grammh_aspro , xamhloterh_grammh_mauro );
        }
        return TRUE;
    }
    // Den exei mirmigia => Den mporei na beltiwsei allo to value.
    if( ants[ position->turn ] == 0 )
    {
        if (depth == 1 && flag_teleiwse == FALSE )
        {
            flag_teleiwse = TRUE;
            printf("teleiwse!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
        return TRUE;
    }

    // O antipalos den exei mirmigia kai den uparxei fai => Den mporei na allaksei to value.
    if( ants[ getOtherSide( position->turn ) ] == 0 && food == 0 )
    {
        if (depth == 1 && flag_teleiwse == FALSE )
        {
            flag_teleiwse = TRUE;
            printf("teleiwse!!!!!!!!!!!!!!!!!!!!!!!!\\n");
        }
        return TRUE;
    }

    // Den mporei na kerdisei akoma kai an ola pane teleia.
    int best_score_change = ants[ position->turn ] + food;
    if( position->score[ position->turn ] + best_score_change < position->score[ getOtherSide( position->turn ) ] )
    {
        if (depth == 1 && flag_parathse == FALSE )
        {
            flag_parathse = TRUE;
            printf("paratise!!!!!!!!!!!!!!!!!!!!!!!!\\n");
        }
        return TRUE;
    }
    // Den mporei na xasei akoma kai an ola pane xalia
    int worst_score_change = ants[ getOtherSide( position->turn ) ] + food;
    if( position->score[ getOtherSide( position->turn ) ] + worst_score_change < position->score[ position->turn ] )
    {
        if (depth == 1 && flag_parathse == FALSE )
        {
            flag_parathse = TRUE;
            printf("paratise!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
        return TRUE;
    }
    return FALSE;
}

// score , murmugkia, fai
static int weigth[3] = { 10 , 10 , -2 };

int utility( Position* position )
{
	int my_value = position->score[ goodies_color ] * weigth[0];
    int enemy_value = position->score[ badies_color ] * weigth[0];

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
    my_value += ants[ goodies_color ] * weigth[1];
    enemy_value += ants[ badies_color ] * weigth[1];
    int food_value = food * weigth[2];
    // to fai an einai sto board den exei value, an to xw faei 8a dwsei 1, an to xei faei o ex8ros 8a dwsei -1.
    // Etsi to parotrinw na to faei kai na empodisei ton ex8ro na to faei. Epishs den iperektimw thn aksia tou.

    return my_value - enemy_value + food_value;;
}


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

int call_max( Position* position , Move* temp_move , int depth , int best_move_value )
{
    Position new_position;
    copy_position( position , &new_position );
    doMove2( &new_position , temp_move );

    int value = max_value( new_position , depth );

    if( best_move_value > value )
        best_move_value = value;
    return best_move_value;
}

int call_min( Position* position , Move* temp_move , int depth , int best_move_value )
{
    Position new_position;
    copy_position( position , &new_position );
    doMove2( &new_position , temp_move );

    int value = min_value( new_position , depth );

    if( best_move_value < value )
        best_move_value = value;
    return best_move_value;
}

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

int player_direction( Position* pos )
{
    if( pos->turn == WHITE )		// find movement's direction
        return 1;
    else
        return -1;
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


// mporoun na ginoun polla inline