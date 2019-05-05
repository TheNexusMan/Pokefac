/**
@brief Class Pokemon, contient les fonctions et données relatives aux pokémons

@author pokeFac team
@file pokemon.h
@version 1.0
@date 19/03/2019

*/
#ifndef _POKEMON_H
#define _POKEMON_H

#include <string.h>
#include <iostream>

using namespace std;

//! \brief Structure stockant les attaques
struct attack
{
	string name; 
	unsigned int damagePoints;
};

//! \brief Gère tout ce qui touche les pokemons

class Pokemon
{
public:

	unsigned int id, level, health, maxHealth, attackStat, defenseStat, isFound;
	string name, type, namePic;
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