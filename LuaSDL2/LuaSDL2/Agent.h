#ifndef _AGENT_H_ 
#define _AGENT_H_ 

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Utils.h"
#include "GameTexture.h"

//The agent that will move around on the screen
class Agent
{
    public:
		//The dimensions of the agent
		static const int AGENT_WIDTH = 20;
		static const int AGENT_HEIGHT = 20;

		//Maximum axis velocity of the agent
		static const int AGENT_VEL = 1;

		Agent( int x, int y, GameTexture* agentTexture);

		//Takes key presses and adjusts the agent's velocity
		void handleEvent( SDL_Event& e );

		//Moves the agent and checks collision
		void move( SDL_Rect& square, Circle& circle, int width, int height );

		//Shows the agent on the screen
		void render();

		//Gets collision circle
		Circle& getCollider();
		Circle& getCollider(SDL_Point newPos);


		//The X and Y offsets of the agent
		SDL_Point mPos;

		//The velocity of the agent
		Vector mVel;
		
		//Agent's collision circle
		Circle mCollider;
		Circle mColliderNext;

				//Moves the collision circle relative to the agent's offset
		void setPosition(int x, int y);
		void setPosition(SDL_Point newPos);
private:		
		
		GameTexture * mAgentTexture;


};


#endif