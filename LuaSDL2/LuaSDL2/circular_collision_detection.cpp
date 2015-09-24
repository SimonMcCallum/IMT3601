/*This source code is based on the work of Lazy Foo' Productions (2004-2013)
This can be redistributed with acknowledgment
*/

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"
#include "Agent.h"
#include "Collidable.h"
#include "GameTexture.h"

//Added for lua C++ linking
#include <lua.hpp>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int setupPositionX = 20;
int setupPositionY = 100;

//Globals
std::vector<Collidable>  collidables;

double distanceSquared( int x1, int y1, int x2, int y2 )
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
};



Agent* agent=NULL;     //
Agent* otherAgent=NULL;//;
SDL_Rect wall;
lua_State *L;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
GameTexture * gAgentTexture = NULL;





bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Enable VSync
		if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
		{
			printf( "Warning: VSync not enabled!" );
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				gAgentTexture = new GameTexture(gWindow,gRenderer);
				agent = new Agent(Agent::AGENT_WIDTH / 2, Agent::AGENT_HEIGHT / 2 , gAgentTexture);
				otherAgent = new Agent(setupPositionX, setupPositionY , gAgentTexture);



/*				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				*/

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load agent texture
	if( !gAgentTexture->loadFromFile( "agent.bmp" ) )
	{
		printf( "Failed to load agent texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gAgentTexture->free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	free(gAgentTexture);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}





void move(Agent* agent)
{
	bool Collision = false;
	SDL_Point newPos;
	
    //Move the agent left or right
	newPos.x = agent->mPos.x + agent->mVel.x;

    //If the agent collided or went too far to the left or right
	if(( newPos.x < 0 ) || 
		( newPos.x + Agent::AGENT_WIDTH > SCREEN_WIDTH )){
			Collision = true;
	}

	newPos.y = agent->mPos.y + agent->mVel.y;
    //If the agent collided or went too far to the up or down
	if(( newPos.y < 0 ) || 
		( newPos.y + Agent::AGENT_HEIGHT > SCREEN_HEIGHT)){
			Collision = true;
	}

	/*
	for (std::vector<Collidable>::iterator it = collidables.begin(); it != collidables.end(); ++it)	{		
		std::cout << " " << *it.getCenter();
		if checkCollision( agent->mCollider, *it){
				Collision = true;
			}
	}
	*/

	if (Collidable::checkCollision(agent->getCollider(newPos),otherAgent->getCollider()))
	{
		Collision = true;
	}

	if (Collidable::checkCollision(agent->getCollider(newPos),wall))
	{
		Collision = true;
	}

	if (!Collision){
		agent->setPosition(newPos);
	}
    
  
}




// LUA section added
int ClosestEnemy(lua_State *L)
{
  int argc = lua_gettop(L);
  int distx =0, disty =0;

  std::cerr << "-- my_function() called with " << argc
    << " arguments:" << std::endl;

  for ( int n=1; n<=argc; ++n ) {
    std::cerr << "-- argument " << n << ": "
      << lua_tostring(L, n) << std::endl;
  }
  
  distx = otherAgent->getCollider().x - agent->getCollider().x;
  disty = otherAgent->getCollider().y - agent->getCollider().y;


  lua_pushnumber(L, distx); // return value
  lua_pushnumber(L, disty); // return value
  return 2; // number of return values
}

void report_errors(lua_State *L, int status)
{
  if ( status!=0 ) {
    std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
}


 /* call a function `AI' defined in Lua */
double AIUpdate(double x, double y) {
	double z;
	/* push functions and arguments */
	lua_getglobal(L, "findEnemy");  /* function to be called */
	lua_pushnumber(L, x);   /* push 1st argument */
	lua_pushnumber(L, y);   /* push 2nd argument */

	/* do the call (2 arguments, 1 result) */
	if (lua_pcall(L, 2, 1, 0) != 0){
		std::cerr << L, "error running function `f':", lua_tostring(L, -1);
	}
	/* retrieve result */
	if (!lua_isnumber(L, -1)){
		std::cerr << L, "function `f' must return a number";
	}
      z = lua_tonumber(L, -1);
      lua_pop(L, 1);  /* pop returned value */
      return z;
    }



int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			L = lua_open();   /* opens Lua */
			luaL_openlibs(L);             /* opens the basic library */
			lua_register(L, "getBadGuy", ClosestEnemy);
			
			int s = luaL_loadfile(L, "testAI.lua");
			if ( s==0 ) {
				// execute Lua program
				s = lua_pcall(L, 0, LUA_MULTRET, 0);
			}
			report_errors(L, s);

			lua_getglobal(L, "enemyX");
			setupPositionX = lua_tonumber(L,-1);
			lua_pop(L,1);

			lua_getglobal(L, "enemyY");
			setupPositionY = lua_tonumber(L,-1);
			lua_pop(L,1);

			otherAgent->setPosition(setupPositionX, setupPositionY);

 
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The agent that will be moving around on the screen

			//Set the wall
			wall.x = 313;
			wall.y = 40;
			wall.w = 40;
			wall.h = 400;
			
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the agent
					agent->handleEvent( e );
					otherAgent->handleEvent( e );
				}

				AIUpdate(0.2,0.3); //

				//Move the agent and check collision
				move(agent); //wall, otherAgent->getCollider() , SCREEN_WIDTH, SCREEN_HEIGHT  );

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render wall
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );		
				SDL_RenderDrawRect( gRenderer, &wall );
				
				//Render agents
				agent->render();
				otherAgent->render();

				//Update screen
				SDL_RenderPresent( gRenderer );
			} //While quit
		lua_close(L);
		std::cerr << std::endl;
		}
	}
	
	//Free resources and close SDL
	close();

	return 0;
}