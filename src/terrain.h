#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "player.h"

using namespace std;

const int SIZETERRAIN = 20;

class terrain{
public:
	int idTerrain;
	char terrainTab[SIZETERRAIN][SIZETERRAIN];

	terrain();
	void initTerrain(int idTerrain); //Initialise le terrain en fonction de son id
	void displayTerrain(player mainPlayer); // Affiche le terrain
};

#endif