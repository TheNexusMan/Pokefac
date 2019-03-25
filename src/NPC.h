/**
@brief Class NPC, contient les fonctions et données relatives aux NPC, hérite de la classe character

@author pokeFac team
@file NPC.h
@version 1.0
@date 19/03/2019

*/
#ifndef _NPC_H
#define _NPC_H

#include "character.h"
#include <iostream>
#include <fstream>
#include "pokemon.h"

using namespace std;


class NPC : public character
{
public:
	unsigned int id;
	char orientation;
	unsigned int nbDialog;
	string dialog[4];
	pokemon NPCPokemon;
	string terrainName;

	/**
	@brief
	Constructeur de la classe NPC
	
	@param none
	@return none

	Exemple Code Block / Visual
	@code
	NPC Harry;
	@endcode
	*/
	NPC();

	/**
	@brief
	Destrcuteur de la classe NPC
	
	@param none
	@return none

	Exemple Code Block / Visual
	@code
	none
	@endcode
	*/
	~NPC();

	/**
	@brief
	Retourne l'orientation du NPC (n = Nord, s = Sud, e = Est, o = Ouest)
	
	@param none
	@return orientation

	Exemple Code Block / Visual
	@code
	NPC.getOrientation();
	@endcode
	*/
	char getOrientation();
};

#endif