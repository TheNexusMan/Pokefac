#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const int sizeTerrain = 20;

class terrain{
public:
	int idTerrain;
	char terrainTab[sizeTerrain][sizeTerrain];

	terrain();
	void initTerrain(int idTerrain); //Initialise le terrain en fonction de son id
	void displayTerrain(); // Affiche le terrain
};

#endif