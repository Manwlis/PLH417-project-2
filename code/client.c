#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>

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
	struct timeval  tv1, tv2;
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
				#if !LOGGING
					printPosition( &gamePosition );
				#endif
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

			case NM_REQUEST_MOVE:		//server requests our move
			
				gettimeofday(&tv1, NULL);

				myMove.color = myColor;
				
				num_moves = 0;
				min_num = 0;
				max_num = 0;
				max_depth = 0;

				if( !canMove( &gamePosition, myColor ) )
				{
					myMove.tile[ 0 ][ 0 ] = -1;		//null move
				}
				else
				{		
					minimax_decision( &gamePosition , &myMove );
				}
// TO_DO: na dokimasw xeirokinita dead_diff kai food_diff

				gettimeofday(&tv2, NULL);

				sendMove( &myMove, mySocket );			//send our move
				// to krataw gia thn ektupwsh. otan steilei o server to neo position, 8a dei o client ta pragmatika apotelesmata.
				doMove2( &gamePosition, &myMove );

				// track stats
				turn++;
				if( num_moves > moves_max )
					moves_max = num_moves;

				// ektupwsh
				#if LOGGING
				printf("%d %d %d %f\n" , turn , min_num , max_num ,
					(double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
				fflush(stdout);
				#else
					printf("!!!!!! TURN: %d !!!!!! ---------------------------------------\n" , turn );
					printPosition( &gamePosition );
					printf("Num legal moves: %d\n" , num_moves );
					printf("I chose to go from (%d,%d), to (%d,%d)\n",myMove.tile[0][0],myMove.tile[1][0],myMove.tile[0][1],myMove.tile[1][1]);
					//printf("Plh8os kombwn: %d , %d\n", min_num , max_num );
					printf ("Total time = %f seconds\n",
							(double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
							(double) (tv2.tv_sec - tv1.tv_sec));
					#if NO_STOP_AT_VOLATILE
						printf("Max depth: %d\n" , max_depth);
					#endif
					printf("--------------------------------------------------------------\n" );
				#endif
				
				break;

			case NM_QUIT:			//server wants us to quit...we shall obey
				printf("\nMoves max: %d \n" , moves_max);
				close( mySocket );
				return 0;
		}
	}
	return 0;
}

