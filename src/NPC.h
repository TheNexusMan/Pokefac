/**
@brief Class NPC, contient les fonctions et données relatives aux NPC, hérite de la classe Character

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


class NPC : public Character
{
public:
	unsigned int id;
	unsigned int nbDialog;
	string dialog[4];
	Pokemon NPCPokemon;
	string terrainName;
	bool beaten = false;
	string image;

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
};

#endif