#ifndef _WORLD
#define _WORLD

#include <iostream>
#include "terrain.h"
#include "pokemon.h"
//#include <SDL.h>
//#include <SDL_image.h>

const unsigned int NBPOKEMON = 3;

class world{
public:
	terrain terrain(1);
	NPC NPCTab[10];
	player mainPlayer;
	pokemon poke[NBPOKEMON];

	void displayTerrain();

	world();


};

#endif