#ifndef _POKEMON_H
#define _POKEMON_H

#include "attack.h"

class pokemon 
{
	Private: 

	unsigned int id, level, exp, health, maxHealth, attackStat, defenseStat;
	string name, type;
	bool isFound;
	attack attackChoice[4];

};

#endif