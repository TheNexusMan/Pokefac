#ifndef _WORLD
#define _WORLD

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class world{
public:
	terrain terrain;
	NPC NPCTab[10];
	player mainPlayer;

	void displayTerrain(){

	}
};

#endif