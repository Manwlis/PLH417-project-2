#include "state.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move )
{
    int value;
    int best_move_value = INT_MIN;

    Position new_position;

    // elenxos pidimatos
    int jump_flag = jump_possible( position );

    // briskei nomimes kiniseis
    Move legal_moves[MAX_LEGAL_MOVES];
    int legal_moves_num;
    if( goodies_color == WHITE )
        legal_moves_num = find_moves_white( position , legal_moves , jump_flag );
    else
        legal_moves_num = find_moves_black( position , legal_moves , jump_flag );
    
    // init stats
    position->ants[WHITE] = count_pieces( position , WHITE );
    position->ants[BLACK] = count_pieces( position , BLACK );
    position->food_diff[0] = 0;
    position->food_diff[1] = 0;
    position->dead_diff[0] = 0;
    position->dead_diff[1] = 0;

    // den xreiazetai na koitaksw gia ean den iparxoun dia8esimes kiniseis giati tote den ksekinaei o algori8mos
    // dokimazei oles
    for( int i = 0 ; i < legal_moves_num ; i++)
    {
        // kanei thn kinhsh
        copy_position( position , &new_position );
        doMove2( &new_position , &(legal_moves[i]) );

        int value = min_value( new_position , 0 , INT_MIN , INT_MAX );

        if( best_move_value < value )
        {
            best_move_value = value;
            copy_move( &(legal_moves[i]) , move );
        }  
    }
    num_moves = legal_moves_num; // track statistics
}

int max_value ( Position position , int depth , int a , int b  )
{
    depth++;
    max_num++;

    // elenxos pidimatos
    int jump_flag = jump_possible( &position );

    if ( terminal_test( &position , depth , jump_flag ) == TRUE )
        return utility( &position , jump_flag );

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        Move null_move;
        null_move.color = position.turn;
        null_move.tile[ 0 ][ 0 ] = -1;		//null move

        doMove2( &position , &null_move );
        return min_value( position , depth , a , b );
    }

    //uparxei kinish
    int value;
    int best_move_value = INT_MIN;

    // briskei nomimes kiniseis
    Move legal_moves[MAX_LEGAL_MOVES];
    int legal_moves_num;
    if( position.turn == WHITE )
        legal_moves_num = find_moves_white( &position , legal_moves , jump_flag );
    else
        legal_moves_num = find_moves_black( &position , legal_moves , jump_flag );

    if( MOVE_REORDER_ACTIVE == TRUE )
    {
        // kanei kiniseis kai reorder ta apotelesmata tous
        Position new_positions[legal_moves_num];
        do_moves_and_reorder( &position , new_positions , legal_moves , legal_moves_num );

        // eksereunhsh kinisewn
        for( int i = legal_moves_num - 1 ; i >= 0 ; i--)
        {
            // minimax
            int value = min_value( new_positions[i] , depth , a , b );
            best_move_value = best_move_value < value ? value : best_move_value;

            // a-b prunning
            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b ) // kladema bash b
                return best_move_value;
            a = a < best_move_value ? best_move_value : a; // enhmerwsh a
        }
    }
    else
    {   // den xreiazetai pinaka apo kiniseis an den kanei reorder
        Position new_position;
        // eksereunhsh kinisewn
        for( int i = 0 ; i < legal_moves_num ; i++)
        {
            // kanei kinish
            copy_position( &position , &new_position ); 
            doMove2( &new_position , &(legal_moves[i]) );

            // minimax
            int value = min_value( new_position , depth , a , b );
            best_move_value = best_move_value < value ? value : best_move_value;

            // a-b prunning
            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value >= b ) // kladema bash b
                return best_move_value;
            a = a < best_move_value ? best_move_value : a; // enhmerwsh a
        }
    }    
    return best_move_value;
}

int min_value ( Position position , int depth , int a , int b  )
{
    // stats
    depth++;
    min_num++;

    // elenxos pidimatos
    int jump_flag = jump_possible( &position );

    if ( terminal_test( &position , depth , jump_flag ) == TRUE )
        return utility( &position , jump_flag );

    // den uparxei dia8esimh kinhsh
    if( !canMove( &position , position.turn ) )
    {
        Move null_move;
        null_move.color = position.turn;
        null_move.tile[ 0 ][ 0 ] = -1;		//null move

        doMove2( &position , &null_move );
        return max_value( position , depth , a , b );
    }

    //uparxei kinish
    int value;
    int best_move_value = INT_MAX;

    // briskei nomimes kiniseis
    Move legal_moves[MAX_LEGAL_MOVES];
    int legal_moves_num;
    if( position.turn == WHITE )
        legal_moves_num = find_moves_white( &position , legal_moves , jump_flag );
    else
        legal_moves_num = find_moves_black( &position , legal_moves , jump_flag );

    if( MOVE_REORDER_ACTIVE == TRUE )
    {
        // kanei kiniseis kai reorder ta apotelesmata tous
        Position new_positions[legal_moves_num];
        do_moves_and_reorder( &position , new_positions , legal_moves , legal_moves_num );

        // eksereunhsh kinisewn anapoda logo sort tou reorder.
        for( int i = 0 ; i < legal_moves_num ; i++)
        {
            // minimax
            int value = max_value( new_positions[i] , depth , a , b );
            best_move_value = best_move_value > value ? value : best_move_value;

            // a-b prunning
            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a ) // kladema bash a
                return best_move_value;
            b = b > best_move_value ? best_move_value : b; // enhmerwsh b
        }
    }
    else
    {   // den xreiazetai pinaka apo kiniseis an den kanei reorder
        Position new_position;

        for( int i = legal_moves_num - 1 ; i >= 0 ; i--)
        {
            // kanei kinish
            copy_position( &position , &new_position ); 
            doMove2( &new_position , &(legal_moves[i]) );

            // minimax
            int value = max_value( new_position , depth , a , b );
            best_move_value = best_move_value > value ? value : best_move_value;

            // a-b prunning
            if( A_B_PRUNING_ACTIVE == TRUE && best_move_value <= a ) // kladema bash a
                return best_move_value;
            b = b > best_move_value ? best_move_value : b; // enhmerwsh b
        }
    }
    return best_move_value;
}

int terminal_test( Position* position , int depth , int jump_flag )
{
    if ( depth > max_depth)
        max_depth = depth;
    // den afhnw na stamathsei an exei pidima gia na meiw8ei horizon effect
    if ( depth >= SEARCH_DEPTH )
    {
        if( NO_STOP_AT_VOLATILE == TRUE && jump_flag == TRUE )
        {
            ; // sunexizei
        }
        else
        {
            return TRUE;
        }
    }
    // printf("depth: %d , white: %d , black: %d\n" , depth , position->ants[WHITE] , position->ants[BLACK] );
    // printf("score white: %d , score black: %d\n" , position->score[WHITE] , position->score[BLACK] );
    // statistika gia to position
    int food_remaining = 0;
    int upsulotero_grammh_aspro = -1;
    int xamhloterh_grammh_mauro = 12;

    for( int i = 0; i < BOARD_ROWS; i++ )
    {
        for( int j = 0; j < BOARD_COLUMNS; j++ )
        {
            food_remaining += position->board[i][j] == RTILE;

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
    if( position->ants[ goodies_color ] == 0 )
        return TRUE;

    // O antipalos den exei mirmigia kai den uparxei fai => Den mporei na allaksei to value.
    if( position->ants[ badies_color ] == 0 && food_remaining == 0 )
        return TRUE;

    // efoson den gnwrizw pio fai edwse pragmati ba8mo, pairnw tis xeiroteres periptwseis.
    int best_score_change = position->ants[ goodies_color ] + food_remaining;
    int worst_score_change = position->ants[ badies_color ] + food_remaining;

    // Den mporei na kerdisei akoma kai an ola pane teleia.
    // xeirwterh periptwsh: olo to fai mou edwse ponto kai kanena tou ex8rou
    if( position->score[ goodies_color ] + best_score_change < position->score[ badies_color ] - position->food_diff[badies_color] ) 
        return TRUE;
    
    // Den mporei na xasei akoma kai an ola pane xalia
    // xeirwterh periptwsh: kanena fai mou dn edwse ponto kai dwsan ola tou ex8rou
    if( position->score[ badies_color ] + worst_score_change < position->score[ goodies_color ] - position->food_diff[goodies_color] )
        return TRUE;
    
    return FALSE;
}

// score , murmugkia , fai , jump
const int weigth[4] = { 10 , 15 , 5 , 10 };

int utility( Position* position , int jump_flag )
{
    // afou dn kserw an to fai 8a dwsei ponto, tou dinw miso baros.
	int my_value = ( position->score[ goodies_color ] - position->food_diff[ goodies_color ] ) * weigth[0]; 
    int enemy_value = ( position->score[ badies_color ] - position->food_diff[ badies_color ] ) * weigth[0];

    // zwntana mirmigkia
    my_value += position->ants[ goodies_color ] * weigth[1];
    enemy_value += position->ants[ badies_color ] * weigth[1];

    // fai
    my_value += position->food_diff[goodies_color] * weigth[2];
    enemy_value += position->food_diff[badies_color] * weigth[2];

    // gia na meiw8ei to horizon effect
    int jump_value = 0;
    if( jump_flag == TRUE )
    {
        jump_value = weigth[3];
        if(position->turn == badies_color)
            jump_value = -jump_value;
    }

    return my_value - enemy_value + jump_value;
}


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

int find_moves_white( Position* position , Move* legal_moves , int jump_flag )
{
    // kateu8unsh paixth
    int column_direction = player_direction( position );

    int legal_moves_num = 0;

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

                /******** jump not possible ********/
                if ( jump_flag == FALSE )
                {
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * column_direction ;
                    temp_move.tile[ 0 ][ 2 ] = -1; // mia kinish an den uparxei pidima

                    // kinish aristera
                    temp_move.tile[ 1 ][ 1 ] = j - 1;
                    if( isLegal( position , &temp_move ))
                    {
                        copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                        legal_moves_num++;
                    }
                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( position , &temp_move ))
                    {
                        copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                        legal_moves_num++;
                    }        
                }
                /******** Jump possible ********/
                else if ( canJump( i , j , position->turn , position ) )
                {
                    temp_move.tile[0][1] = temp_move.tile[0][0] + 2 * column_direction;
                    for ( int row_direction1 = -2 ; row_direction1 <= 2 ; row_direction1 += 4)
                    {
                        temp_move.tile[1][1] = temp_move.tile[1][0] + row_direction1;
                        temp_move.tile[0][2] = -1;
                        
                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                        {
                            copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                            legal_moves_num++;
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
                                    copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                    legal_moves_num++;
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
                                            copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                            legal_moves_num++;
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
                                                    copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                                    legal_moves_num++;
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                                            legal_moves_num++;
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
    return legal_moves_num;
}

int find_moves_black( Position* position , Move* legal_moves , int jump_flag )
{
    // kateu8unsh paixth
    int column_direction = player_direction( position );

    int legal_moves_num = 0;

    Move temp_move;
    temp_move.color = position->turn;

    for( int i = BOARD_ROWS; i >= 0; i-- ) // ksekinaw apo ta pisw. Exoun perissoteres pi8anothtes na bgaloun kati kalo
    {
        for( int j = BOARD_COLUMNS; j >= 0; j-- )
        {
            if( position->board[ i ][ j ] == position->turn ) // diko tou pioni
            {
                //piece we are going to move
                temp_move.tile[ 0 ][ 0 ] = i;
                temp_move.tile[ 1 ][ 0 ] = j;

                /******** jump not possible ********/
                if ( jump_flag == FALSE )
                {
                    temp_move.tile[ 0 ][ 1 ] = i + 1 * column_direction ;
                    temp_move.tile[ 0 ][ 2 ] = -1; // mia kinish an den uparxei pidima

                    // kinish aristera
                    temp_move.tile[ 1 ][ 1 ] = j - 1;
                    if( isLegal( position , &temp_move ))
                    {
                        copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                        legal_moves_num++;
                    }
                    // kinish deksia
                    temp_move.tile[ 1 ][ 1 ] = j + 1;
                    if( isLegal( position , &temp_move ))
                    {
                        copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                        legal_moves_num++;
                    }        
                }
                /******** Jump possible ********/
                else if ( canJump( i , j , position->turn , position ) )
                {
                    temp_move.tile[0][1] = temp_move.tile[0][0] + 2 * column_direction;
                    for ( int row_direction1 = -2 ; row_direction1 <= 2 ; row_direction1 += 4)
                    {
                        temp_move.tile[1][1] = temp_move.tile[1][0] + row_direction1;
                        temp_move.tile[0][2] = -1;
                        
                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                        {
                            copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                            legal_moves_num++;
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
                                    copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                    legal_moves_num++;
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
                                            copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                            legal_moves_num++;
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
                                                    copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                                    legal_moves_num++;
                                                }
                                                else
                                                {
                                                    temp_move.tile[0][5] = temp_move.tile[ 0 ][ 4 ] + 2 * column_direction;
                                                    for ( int row_direction5 = -2 ; row_direction5 <= 2 ; row_direction5 += 4)
                                                    {
                                                        temp_move.tile[1][5] = temp_move.tile[1][4] + row_direction5;
                                                        if( isLegal( position , &temp_move )) // an einai legal den uparxei allo pidima
                                                        {
                                                            copy_move( &temp_move , &(legal_moves[ legal_moves_num ]) );
                                                            legal_moves_num++;
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
    return legal_moves_num;
}

void do_moves_and_reorder( Position* position , Position* new_positions , Move* move_array , int moves_num )
{
    // kanei oles tis kiniseis
    for( int i = 0 ; i < moves_num ; i++)
    {
        copy_position( position , &(new_positions[i]) );
        doMove2( &(new_positions[i]) , &(move_array[i]) );
    }
    // briskei values
    for( int i = 0 ; i < moves_num ; i++)
        new_positions[i].heurestic_value = heurestic_value( &(new_positions[i]) , jump_possible( &(new_positions[i]) ) );
    // sort bash values
    qsort( new_positions , moves_num , sizeof(Position) , comparitor );
}

int comparitor( const void * lhs , const void * rhs )
{
    return ( ( (Position*) lhs )->heurestic_value - ( (Position*) rhs )->heurestic_value );
}