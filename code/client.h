#ifndef _CLIENT_H
#define _CLIENT_H

#include "global.h"
#include "board.h"
#include "move.h"
#include "comm.h"
#include "state.h"

/**********************************************************/
Position gamePosition;		// Position we are going to use

Move myMove;				// move to save our choice and send it to the server

char myColor;				// to store our color
int mySocket;				// our socket

char * agentName = "SuperAI";

char * ip = "127.0.0.1";	// default ip (local machine)
/**********************************************************/

#endif