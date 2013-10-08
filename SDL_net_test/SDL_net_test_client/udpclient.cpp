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
 
#include <SDL.h>
#include <SDL_net.h>
 
int main(int argc, char **argv)
{
	UDPsocket udpsock;         /* Socket descriptor */
	IPaddress server_address;  /* the server address */
	UDPpacket *packet;         /* Pointer to packet memory */
	int quit;
	int x=23;
	int y=15;
	char * server_name = "127.000.000.001";  // This is the default server name, and creates enough memory to store other names from argv[1]
	Uint16 port_number = 8880;  // This is a default port that is overridden by argv[2]
	Uint16 default_client_port = 8881; // set to 0 for a random port
 

	/* Check for parameters	if there are three overwrite otherwise we will be using default values */
	if (argc == 3)
	{
		server_name = argv[1];
		port_number = atoi(argv[2]);
	} else {
		fprintf(stderr, "Usage: udpclient host port (default: updclient %s %d ) \n", server_name, port_number);
	}


	/* Initialize SDL */
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
	if (!(udpsock = SDLNet_UDP_Open(default_client_port)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
		/* Open a socket on random port */
	if (!(udpsock = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Resolve server name into server address */
	if (SDLNet_ResolveHost(&server_address, server_name, port_number) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n",server_name ,port_number, SDLNet_GetError());
		exit(EXIT_FAILURE);
	}


	/* Make space for the packet */
	if (!(packet = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}



	/* Main loop */
	quit = 0;
	while (!quit)
	{
		printf("Fill the buffer\n>");
		scanf("%s", (char *)packet->data);
		packet->data[8]=(Uint8)x;
		packet->data[9]=(Uint8)0;
		packet->data[10]=(Uint8)0;
		packet->data[11]=(Uint8)0;
		packet->data[12]=(Uint8)y;
		packet->data[13]=(Uint8)0;
		packet->data[14]=(Uint8)0;
		packet->data[15]=(Uint8)0
			;

 
		packet->address.host = server_address.host;	/* Set the destination host */
		packet->address.port = server_address.port;	/* And destination port */
 
		packet->len = 24;
		SDLNet_UDP_Send(udpsock, -1, packet); /* This sets the p->channel */
 
		/* Quit if packet contains "quit" */
		if (!strcmp((char *)packet->data, "quit"))
			quit = 1;
	}
 
	/* Clean and exit */
	SDLNet_FreePacket(packet);
	SDLNet_Quit();
	return EXIT_SUCCESS;
}