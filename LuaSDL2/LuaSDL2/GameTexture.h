#ifndef _GAMETEXTURE_H_ 
#define _GAMETEXTURE_H_ 

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Texture wrapper class
class GameTexture
{
	public:

		GameTexture(SDL_Window* gWindow, SDL_Renderer* gRenderer);

		~GameTexture();

		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//frees the texture memory
		void free();

		//Set using 8 bit integers characters
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, 
			SDL_Rect* clip = NULL, 
			double angle = 0.0, 
			SDL_Point* center = NULL, 
			SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//member pointers to rendering 
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		//Image dimensions
		int mWidth;
		int mHeight;
};
#endif