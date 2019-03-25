/**
@brief Class CharacterTexture, contient les fonctions et données relatives aux textures des personnages

@author pokeFac team
@file CharacterTexture.h
@version 1.0
@date 19/03/2019

*/
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class CharacterTexture
{
public:
	CharacterTexture();
	~CharacterTexture();

	void loadImage();


private:


	SDL_Surface * leftSide;
	SDL_Surface * rightSide;
	SDL_Surface * frontSide;
	SDL_Surface * backSide;

};

