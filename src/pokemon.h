#ifndef _POKEMON_H
#define _POKEMON_H

#include <string.h>
#include <iostream>

using namespace std;

struct attack
{
	string name; 
	unsigned int damagePoints;
};

class pokemon
{
public:

	unsigned int id, level, health, maxHealth, attackStat, defenseStat, isFound;
	string name, type;
	attack attackChoice[4];

	/**
	@brief 
	Retire le nombre de point d'attaque à la vie du Pokémon passé en paramètre
	
	@param poke, att
	@return none
	
	Exemple Code Block / Visual
	@code
	poke.receiveAttack(poke, attack);
	@endcode */
	void receiveAttack(attack att);

	/**
	@brief 
	Affiche la vie du Pokémon sur sa vie maximum (health / maxHealth)
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	poke.displayHealth();
	@endcode */
	void displayHealth() const;

	/**
	@brief 
	Affiche les infos de base du Pokémon
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	poke.displayInfos();
	@endcode */
	void displayInfos() const;
};

#endif