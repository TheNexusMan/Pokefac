#ifndef _NPC_H
#define _NPC_H

#include "character.h"
#include <iostream>
#include <fstream>
#include "pokemon.h"

using namespace std;


class NPC :
	public character
{
public:
	NPC();
	~NPC();
	char getRotation(); // Detecte la rotation des pnj pour la ligne (n, s, e ou o)
					   // n = Nord; s = Sud; e = Est; o = Ouest
	unsigned int id;
	char rotation;
	unsigned int nbDialog;
	string dialog[4];
	pokemon NPCPokemon;
};

#endif