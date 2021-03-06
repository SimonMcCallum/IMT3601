/*
This code is adapted from the game programming wiki under the 
Gnu Free Documentation licence v1.2
http://www.gnu.org/licenses/old-licenses/fdl-1.2.txt

Original tutorial
http://content.gpwiki.org/index.php/SDL:Tutorial:Using_SDL_net

Updated by Simon McCallum October 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__

// MacOSX specific
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>

#else

// Windows or Linux
#include <SDL.h>
#include <SDL_net.h>

#endif
 
int main(int argc, char **argv)
{
	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */
	int quit;
 
	/* Initialize SDL_net */
	if (SDL_Init(0) < 0)
	{
		fprintf(stderr, "SDL_Init: \n");
		exit(EXIT_FAILURE);
	}

	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Open a socket */
	if (!(sd = SDLNet_UDP_Open(8880)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Make space for the packet */
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Main loop */
    printf("Started up the UDP Server on port 8880\n");
	quit = 0;
	while (!quit)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		if (SDLNet_UDP_Recv(sd, p))
		{
			printf("UDP Packet incoming\n");
			printf("\tChan:    %d\n", p->channel);
			printf("\tData:    %s\n", (char *)p->data);
			printf("\tx,y:    %X\n", ((Uint32 *)p->data)[0]);
			printf("\tx,y:    %X\n", ((Uint32 *)p->data)[1]);
			printf("\tx:    %d\n", ((Uint32 *)p->data)[2]);
			printf("\ty:    %d\n", ((Uint32 *)p->data)[3]);
			printf("\tLen:     %d\n", p->len);
			printf("\tMaxlen:  %d\n", p->maxlen);
			printf("\tStatus:  %d\n", p->status);
			printf("\tAddress: %x %x\n", p->address.host, p->address.port);
 
			/* Quit if packet contains "quit" */
			if (strcmp((char *)p->data, "quit") == 0)
				quit = 1;
		}
		else
		{
			SDL_Delay(20);
		}
	}
 
	/* Clean and exit */
	SDLNet_FreePacket(p);
	SDLNet_Quit();
	return EXIT_SUCCESS;
}