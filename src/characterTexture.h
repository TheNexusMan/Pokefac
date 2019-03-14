#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class characterTexture
{
public:
	characterTexture();
	~characterTexture();

	void loadImage();


private:


	SDL_Surface * leftSide;
	SDL_Surface * rightSide;
	SDL_Surface * frontSide;
	SDL_Surface * backSide;

};

