#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "player.h"

using namespace std;

const int SIZETERRAIN = 20;


class terrain{
public:
	int idTerrain;
	char terrainTab[SIZETERRAIN][SIZETERRAIN];
	string terrainName;

	terrain();
	void initTerrain(int idTerrain,string nameTerrain); //Initialise le terrain en fonction de son id
	void displayTerrain(player mainPlayer); // Affiche le terrain
};

#endif