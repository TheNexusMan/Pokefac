#ifndef _TERRAIN
#define _TERRAIN

#include <iostream>
#include <fstream>
#include <stdlib.h>

const int sizeTerrain = 20;

class terrain{
public:
	int idTerrain;
	char terrain[sizeTerrain][sizeTerrain];

	void initTerrain(int idTerrain); //Initialise le terrain en fonction de son id
	void displayTerrain(); // Affiche le terrain
};

#endif