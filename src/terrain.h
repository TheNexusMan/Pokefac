/**
@brief Class terrain, contient les fonctions et données relatives aux terrains

@author pokeFac team
@file terrain.h
@version 1.0
@date 19/03/2019

*/
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
	char terrainTab[SIZETERRAIN][SIZETERRAIN];
	string terrainName;

	/**
	@brief 
	Constructeur de la class terrain
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	terrain mainTerrain;
	@endcode */
	terrain();

	/**
	@brief 
	Initialisation du terrain en fonction du nom passé en paramètre
	
	@param nameTerrain
	@return none
	
	Exemple Code Block / Visual
	@code
	terrain.initTerrain("terrain1");
	@endcode */
	void initTerrain(string nameTerrain);

	/**
	@brief 
	Affiche le terrain et le joueur au bon emplacement
	
	@param mainPlayer
	@return none
	
	Exemple Code Block / Visual
	@code
	terrain.displayTerrain(mainPlayer);
	@endcode */
	void displayTerrain(Player mainPlayer);
};

#endif