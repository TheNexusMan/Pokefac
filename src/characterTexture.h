/**
@brief Class characterTexture, contient les fonctions et données relatives aux textures des personnages

@author pokeFac team
@file characterTexture.h
@version 1.0
@date 19/03/2019

*/
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

