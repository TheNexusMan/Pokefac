#include "pokemon.h"

void pokemon::launchAttack(pokemon poke, attack att)
{ 

	if(poke.health > 0 && poke.health >= (att.damagePoints - poke.defenseStat))
		poke.health = poke.health - (att.damagePoints - poke.defenseStat);
	else if (poke.health < (att.damagePoints - poke.defenseStat))
		poke.health=0;

}

void pokemon::initPokemon(const pokemon & poke)
{
	id = poke.id;
	name = poke.name;
	type = poke.type;
	isFound = poke.isFound;
	level = poke.level;
	health = poke.health;
	maxHealth = poke.maxHealth;
	attackStat = poke.attackStat;
	defenseStat = poke.defenseStat;

	for(unsigned int i = 0; i < 4; i++)
	{
		attackChoice[i].name = poke.attackChoice[i].name;
		attackChoice[i].damagePoints = poke.attackChoice[i].damagePoints;
	}
}