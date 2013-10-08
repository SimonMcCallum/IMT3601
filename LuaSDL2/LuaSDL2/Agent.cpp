#include "Agent.h"

Agent::Agent( int x, int y , GameTexture* agentTexture)
{
    //Initialize the offsets
    mPos.x = x;
	mPos.y = y;
	mAgentTexture = agentTexture;

	//Set collision circle size
	mCollider.r = AGENT_WIDTH / 2;
	mCollider.x = x;
	mCollider.y = y;

    //Initialize the velocity
	mVel.x = 0;
	mVel.y = 0;

}

void Agent::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
			case SDLK_UP: mVel.y -= AGENT_VEL; break;
            case SDLK_DOWN: mVel.y += AGENT_VEL; break;
            case SDLK_LEFT: mVel.x -= AGENT_VEL; break;
            case SDLK_RIGHT: mVel.x += AGENT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVel.y += AGENT_VEL; break;
			case SDLK_DOWN: mVel.y -= AGENT_VEL; break;
			case SDLK_LEFT: mVel.x += AGENT_VEL; break;
			case SDLK_RIGHT: mVel.x -= AGENT_VEL; break;
        }
    }
}



void Agent::render()
{
    //Show the agent
	mAgentTexture->render( mPos.x - mCollider.r, mPos.y - mCollider.r );
}

Circle& Agent::getCollider()
{
	return mCollider;
}

Circle& Agent::getCollider(SDL_Point newPos)
{
	mColliderNext.r = AGENT_WIDTH / 2;
	mColliderNext.x = newPos.x;
	mColliderNext.y = newPos.y;
	return mColliderNext;
}

//example of recursive overloading call.
void Agent::setPosition(SDL_Point newPos)
{
	setPosition(newPos.x, newPos.y);
}

void Agent::setPosition(int x, int y)
{
	//Align collider to center of agent
	mPos.x = x;
	mPos.y = y;
	mCollider.x = x;
	mCollider.y = y;
}
