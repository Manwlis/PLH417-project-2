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
                        value = call_min( position , &temp_move , 0 , best_move_value , INT_MIN , INT_MAX );

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
                        value = call_min( position , &temp_move , 0 , best_move_value , INT_MIN , INT_MAX );

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
                            value = call_min( position , &temp_move , 0 , best_move_value , INT_MIN , INT_MAX );

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
                                    value = call_min( position , &temp_move , 0 , best_move_value , INT_MIN , INT_MAX );

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
                                            value = call_min( position , &temp_move , 0 , best_move_value , INT_MIN , INT_MAX );

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
                                                    value = call_min( position , &temp_move , 0 , best_move_value , INT_MIN , INT_MAX );

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
                                                            value = call_min( position , &temp_move , 0 , best_move_value , INT_MIN , INT_MAX );

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
int max_value ( Position position , int depth , int a , int b  )
{
    depth++;
    max_num++;

    if ( terminal_test( &position , depth ) == TRUE )
        return utility( &position );

    Move temp_move;
    temp_move.color = position.turn;
    Position new_position;

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        return call_min( &position , &temp_move , depth , INT_MIN , a , b );
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

                /******** Jump not possible ********/
                if ( jump_flag == FALSE )
                {
                    // kane ka8e kinish kai epestrepse to kalutero skor. Den xreiazetai na 8umamai ti htan h kinhsh.
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * column_direction;
                    temp_move.tile[ 0 ][ 2 ] = -1; // mia kinish an den uparxei pidima

                    // kinish aristera
                    temp_move.tile[ 1 ][ 1 ] = j - 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        best_move_value = call_min( &position , &temp_move , depth , best_move_value , a , b );

                        // a-b prunning
                        if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b )
                            return best_move_value;
                        a = a < best_move_value ? best_move_value : a;
                    }

                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        // a-b prunning
                        if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b )
                            return best_move_value;
                        a = a < best_move_value ? best_move_value : a;

                        best_move_value = call_min( &position , &temp_move , depth , best_move_value , a , b );
                    }
                }
                /******** Jump possible ********/
                else if ( canJump( i , j , position.turn , &position ) )
                {
                    temp_move.tile[0][1] = temp_move.tile[0][0] + 2 * column_direction;
                    for ( int row_direction1 = -2 ; row_direction1 <= 2 ; row_direction1 += 4)
                    {
                        temp_move.tile[1][1] = temp_move.tile[1][0] + row_direction1;
                        temp_move.tile[0][2] = -1;
                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                        {
                            // a-b prunning
                            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b )
                                return best_move_value;
                            a = a < best_move_value ? best_move_value : a;

                            best_move_value = call_min( &position , &temp_move , depth , best_move_value , a , b );
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
                                    // a-b prunning
                                    if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b )
                                        return best_move_value;
                                    a = a < best_move_value ? best_move_value : a;

                                    best_move_value = call_min( &position , &temp_move , depth , best_move_value , a , b );
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
                                            // a-b prunning
                                            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b )
                                                return best_move_value;
                                            a = a < best_move_value ? best_move_value : a;

                                            best_move_value = call_min( &position , &temp_move , depth , best_move_value , a , b );
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
                                                    // a-b prunning
                                                    if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b )
                                                        return best_move_value;
                                                    a = a < best_move_value ? best_move_value : a;

                                                    best_move_value = call_min( &position , &temp_move , depth , best_move_value , a , b );
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            // a-b prunning
                                                            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b )
                                                                return best_move_value;
                                                            a = a < best_move_value ? best_move_value : a;

                                                            best_move_value = call_min( &position , &temp_move , depth , best_move_value , a , b );
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
                }
            }
        }
    }
    return best_move_value;
}


/* Idia ilopoihsh me to max_value, me monh diafora best_value = INT_MAX kai psaxnw mikrotero */
int min_value ( Position position , int depth , int a , int b  )
{
    // stats
    depth++;
    min_num++;

    if ( terminal_test( &position , depth ) == TRUE )
        return utility( &position );

    Move temp_move;
    temp_move.color = position.turn;
    Position new_position;

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        return call_max( &position , &temp_move , depth , INT_MAX , a , b );
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
                        // a-b prunning
                        if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a )
                            return best_move_value;
                        b = b > best_move_value ? best_move_value : b;

                        best_move_value = call_max( &position , &temp_move , depth , best_move_value , a , b );
                    }

                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( &position , &temp_move ))
                    {
                        // a-b prunning
                        if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a )
                            return best_move_value;
                        b = b > best_move_value ? best_move_value : b;

                        best_move_value = call_max( &position , &temp_move , depth , best_move_value , a , b );
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
                            // a-b prunning
                            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a )
                                return best_move_value;
                            b = b > best_move_value ? best_move_value : b;

                            best_move_value = call_max( &position , &temp_move , depth , best_move_value , a , b );
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
                                    // a-b prunning
                                    if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a )
                                        return best_move_value;
                                    b = b > best_move_value ? best_move_value : b;

                                    best_move_value = call_max( &position , &temp_move , depth , best_move_value , a , b );
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
                                            // a-b prunning
                                            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a )
                                                return best_move_value;
                                            b = b > best_move_value ? best_move_value : b;

                                            best_move_value = call_max( &position , &temp_move , depth , best_move_value , a , b );
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
                                                    // a-b prunning
                                                    if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a )
                                                        return best_move_value;
                                                    b = b > best_move_value ? best_move_value : b;

                                                    best_move_value = call_max( &position , &temp_move , depth , best_move_value , a , b );
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( &position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            // a-b prunning
                                                            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a )
                                                                return best_move_value;
                                                            b = b > best_move_value ? best_move_value : b;

                                                            best_move_value = call_max( &position , &temp_move , depth , best_move_value , a , b );
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

int terminal_test( Position* position , int depth )
{
    if ( depth == SEARCH_DEPTH )
        return TRUE;
    // isws an den exei mirmigia kapios?
    // an ola ta mirmigia mou einai pera apo tou allou
    int ants[2] = { 0 , 0 };
    int food_remaining = 0;

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
                food_remaining++;

            if ( position->board[i][j] == BLACK )
                xamhloterh_grammh_mauro = i; // telutaio mauro
            else if ( position->board[i][j] == WHITE && upsulotero_grammh_aspro == -1 )
                upsulotero_grammh_aspro = i; // prwto aspro
        }
    }

    // den uparxei fai kai den mporei na ginei kapia aixmalwsia.
    if (upsulotero_grammh_aspro > xamhloterh_grammh_mauro && food_remaining == 0 )
        return TRUE;

    // Den exei mirmigia => Den mporei na beltiwsei allo to value. Mallon reduntant giati den 8a ftasei edw pote afou dn 8a exei kiniseis.
    if( ants[ goodies_color ] == 0 )
        return TRUE;

    // O antipalos den exei mirmigia kai den uparxei fai => Den mporei na allaksei to value.
    if( ants[ badies_color ] == 0 && food_remaining == 0 )
        return TRUE;

    // efoson den gnwrizw pio fai edwse pragmati ba8mo, pairnw tis xeiroteres periptwseis.
    // fai pou exw faei = score - pontoi apo basilises. An kapio murmhgki den zei h den exei pe8anei, einai basilisa.
    int my_food = position->score[ goodies_color ] - ( NUM_ANTS - ants[ goodies_color ] - position->dead[ goodies_color ] );
    int enemy_food = position->score[ badies_color ] - ( NUM_ANTS - ants[ badies_color ] - position->dead[ badies_color ] );

    int best_score_change = ants[ goodies_color ] + food_remaining;
    int worst_score_change = ants[ badies_color ] + food_remaining;

    // Den mporei na kerdisei akoma kai an ola pane teleia.
    // xeirwterh periptwsh: olo to fai mou edwse ponto kai kanena tou ex8rou
    if( position->score[ goodies_color ] + best_score_change < position->score[ badies_color ] - enemy_food ) 
        return TRUE;
    

    // Den mporei na xasei akoma kai an ola pane xalia
    // xeirwterh periptwsh: kanena fai mou dn edwse ponto kai dwsan ola tou ex8rou
    if( position->score[ badies_color ] + worst_score_change < position->score[ goodies_color ] - goodies_color )
        return TRUE;
    
    return FALSE;
}

// score , murmugkia, fai
int weigth[3] = { 10 , 15 , 5 };

int utility( Position* position )
{
    int ants[2] = { 0 , 0 };
    int food_remaining = 0;

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            if ( position->board[i][j] == WHITE )
                ants[0]++;
            else if ( position->board[i][j] == BLACK )
                ants[1]++;
            else if ( position->board[i][j] == RTILE )
                food_remaining++;
        }
    }

    // opws kai sto terminal test
    int my_food = position->score[ goodies_color ] - ( NUM_ANTS - ants[ goodies_color ] - position->dead[ goodies_color ] );
    int enemy_food = position->score[ badies_color ] - ( NUM_ANTS - ants[ badies_color ] - position->dead[ badies_color ] );


    // afou dn kserw an to fai edwse pragmati ponto, tou dinw miso baros. An diwr8w8ei, mono gia ta fagomena sto mellon.
	int my_value = ( position->score[ goodies_color ] - my_food ) * weigth[0]; 
    int enemy_value = ( position->score[ badies_color ] - enemy_food)* weigth[0];

    my_value += ants[ goodies_color ] * weigth[1];
    enemy_value += ants[ badies_color ] * weigth[1];

    my_value += my_food * weigth[2];
    enemy_value += enemy_food * weigth[2];

    return my_value - enemy_value ;
}


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

int call_max( Position* position , Move* temp_move , int depth , int best_move_value , int a , int b )
{
    Position new_position;
    copy_position( position , &new_position );

    int ants_before_move = count_pieces( &new_position , goodies_color );

    doMove2( &new_position , temp_move ); // ulopoihsh kinhshs

    new_position.dead[ goodies_color ] += ants_before_move - count_pieces( &new_position , goodies_color ); // metrhma nekrwn

    int value = max_value( new_position , depth , a , b ); // klhsh max_value
    if( best_move_value > value ) // krataei to kalutero skor
        best_move_value = value;
    return best_move_value;
}

int call_min( Position* position , Move* temp_move , int depth , int best_move_value , int a , int b )
{
    Position new_position;
    copy_position( position , &new_position );

    int ants_before_move = count_pieces( &new_position , badies_color );

    doMove2( &new_position , temp_move );

    new_position.dead[ badies_color ] += ants_before_move - count_pieces( &new_position , badies_color );

    int value = min_value( new_position , depth , a , b );
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

    target->dead[0] = source->dead[0];
    target->dead[1] = source->dead[1];
}


// mporoun na ginoun polla inline