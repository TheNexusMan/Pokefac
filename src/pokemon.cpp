#include "pokemon.h"

void pokemon::receiveAttack(pokemon & poke, attack att)
{ 

	if(poke.health > 0 && poke.health >= att.damagePoints)
		poke.health -= att.damagePoints;
	else if (poke.health < att.damagePoints)
		poke.health = 0;

}

void pokemon::initPokemon(const pokemon & poke)
{
	id = poke.id;
	name = poke.name;
	type = poke.type;
	isFound = poke.isFound;
	level = poke.level;
	health = poke.maxHealth;
	maxHealth = poke.maxHealth;
	attackStat = poke.attackStat;
	defenseStat = poke.defenseStat;

	for(unsigned int i = 0; i < 4; i++)
	{
		attackChoice[i].name = poke.attackChoice[i].name;
		attackChoice[i].damagePoints = poke.attackChoice[i].damagePoints;
	}
}

void pokemon::displayHealth()
{
	cout << health << "/" << maxHealth << "PV";
}

void pokemon::displayInfos()
{
	cout << "Id: #" << id << endl;
	cout << "Name: " << name << endl;
	cout << "Type: " << type << endl;
	displayHealth();
}