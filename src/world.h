#ifndef _WORLD
#define _WORLD

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
#include "terrain.h"
#include "pokemon.h"
//#include "NPC.h"
//#include "player.h"

using namespace std;

const unsigned int NBPOKEMON = 3;

class world{
public:
	world();

	terrain worldTerrain;
	//NPC NPCTab[10];
	//player mainPlayer;
	pokemon poke[NBPOKEMON];
};

#endif