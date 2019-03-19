#ifndef _POKEMON_H
#define _POKEMON_H

#include "attack.h"
#include <string.h>
#include <iostream>

using namespace std;

class pokemon 
{
public:

	unsigned int id, level, health, maxHealth, attackStat, defenseStat, isFound;
	string name, type;
	attack attackChoice[4];

	void launchAttack(pokemon poke, attack att); //Fonction qui retourne le pokemon avec des points de vie en moins

	void initPokemon(const pokemon & poke);
};

#endif