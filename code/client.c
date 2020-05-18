#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

int moves_max = 0;
int main( int argc, char ** argv )
{
	int c;
	opterr = 0;

	while( ( c = getopt ( argc, argv, "i:p:h" ) ) != -1 )
		switch( c )
		{
			case 'h':
				printf( "[-i ip] [-p port]\n" );
				return 0;
			case 'i':
				ip = optarg;
				break;
			case 'p':
				port = optarg;
				break;
			case '?':
				if( optopt == 'i' || optopt == 'p' )
					printf( "Option -%c requires an argument.\n", ( char ) optopt );
				else if( isprint( optopt ) )
					printf( "Unknown option -%c\n", ( char ) optopt );
				else
					printf( "Unknown option character -%c\n", ( char ) optopt );
				return 1;
			default:
			return 1;
		}


	connectToTarget( port, ip, &mySocket );

	char msg;

/**********************************************************/
// used in random
	srand( time( NULL ) );
	int i, j, k;
	int jumpPossible;
	int playerDirection;

	int ants_before_move;
	int turn = 0;
/**********************************************************/

	while( 1 )
	{

		msg = recvMsg( mySocket );

		switch ( msg )
		{
			case NM_REQUEST_NAME:		//server asks for our name
				sendName( agentName, mySocket );
				break;

			case NM_NEW_POSITION:		//server is trying to send us a new position
				getPosition( &gamePosition, mySocket );
				printPosition( &gamePosition );

				// tracking killed ants
				gamePosition.dead[0] = 0;
				gamePosition.dead[1] = 0;

				break;

			case NM_COLOR_W:			//server indorms us that we have WHITE color
				myColor = WHITE;
				goodies_color = WHITE;
				badies_color = BLACK;
				printf("My color is %d\n",myColor);
				break;

			case NM_COLOR_B:			//server indorms us that we have BLACK color
				myColor = BLACK;
				goodies_color = BLACK;
				badies_color = WHITE;
				printf("My color is %d\n",myColor);
				break;

			case NM_PREPARE_TO_RECEIVE_MOVE:	//server informs us that he will send opponent's move
				getMove( &moveReceived, mySocket );
				moveReceived.color = getOtherSide( myColor );
				
				// o monos tropos na meiw8oun ta murmhgkia mou sto guro tou allou einai na ta efage
				ants_before_move = count_pieces( &gamePosition , myColor );

				doMove2( &gamePosition, &moveReceived );		//play opponent's move on our position

				gamePosition.dead[myColor] += ants_before_move - count_pieces( &gamePosition , myColor );

				printPosition( &gamePosition );
				printf("W dead: %d , B dead: %d\n" , gamePosition.dead[WHITE] , gamePosition.dead[BLACK] );

				break;

			case NM_REQUEST_MOVE:		//server requests our move
			
				myMove.color = myColor;
				
				num_moves = 0;
				min_num = 0;
				max_num = 0;

				if( !canMove( &gamePosition, myColor ) )
				{
					myMove.tile[ 0 ][ 0 ] = -1;		//null move
				}
				else
				{		
					minimax_decision( &gamePosition , &myMove );
				}

				// o monos tropos na meiw8oun ta murmugkia tou antipalou einai na tou ta faw
				ants_before_move = count_pieces( &gamePosition , getOtherSide(myColor) );

				sendMove( &myMove, mySocket );			//send our move
				doMove2( &gamePosition, &myMove );		//play our move on our position

				gamePosition.dead[ getOtherSide(myColor) ] += ants_before_move - count_pieces( &gamePosition , getOtherSide(myColor) );

				turn++;
				printf("!!!!!! TURN: %d !!!!!!" , turn );

				printf("Num legal moves: %d\n" , num_moves );
				if( num_moves > moves_max )
					moves_max = num_moves;
				printf("I chose to go from (%d,%d), to (%d,%d)\n",myMove.tile[0][0],myMove.tile[1][0],myMove.tile[0][1],myMove.tile[1][1]);
				printf("Plh8os kombwn: %d , %d\n", min_num , max_num );
				printPosition( &gamePosition );

				break;

			case NM_QUIT:			//server wants us to quit...we shall obey
				printf("\nMoves max: %d \n" , moves_max);
				close( mySocket );
				return 0;
		}
	}
	return 0;
}

