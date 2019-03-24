#include "player.h"

void player::moveUp()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x-1, y);
}

void player::moveDown()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x + 1, y);
}

void player::moveLeft()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x, y-1);
}

void player::moveRight()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x, y+ 1);
}

unsigned int player::getMoney()
{
	return money;
}

void player::addMoney(unsigned int adding)
{
	money = money + adding;
}

void player::initPlayer(const pokemon poke)
{	
	setPosX(1);
	setPosY(2); //Place le joueur aux coordonnées (1,2)
	addMoney(100); //Lui donne 100 en Argent
	setPokeball(5); // Lui donne 5 pokeballs
	tabPokemon[0] = poke;
	nbPokemon = 1;
}

void player::setPokeball(int nb)
{
	pokeball += nb;
}

unsigned int player::getPokeball()
{
	return pokeball;
}

void player::addPokemon(const pokemon & poke)
{
	if(hasFreePokeLocation() && !hasThisPokemon(poke))
	{
		tabPokemon[nbPokemon] = poke;
		nbPokemon++;
	}
}

pokemon& player::getPokemon(unsigned int id)
{
	return tabPokemon[id];
}

pokemon player::getPokemon(unsigned int id) const
{
	return tabPokemon[id];
}

bool player::hasThisPokemon(const pokemon & poke)
{
	for(unsigned int i = 0; i < nbPokemon; i++)
	{
		if(tabPokemon[i].id == poke.id) return true;
	}
	return false;
}

pokemon& player::firstPokemonAlive()
{
	unsigned int idPokeAlive = 0;
	while(tabPokemon[idPokeAlive].health <= 0)
	{
		idPokeAlive++;
	}

	return tabPokemon[idPokeAlive];
}

void player::treatAllPokemon()
{
	for(unsigned int i = 0; i < nbPokemon; i++)
	{
		tabPokemon[i].health = tabPokemon[i].maxHealth;
	}
}

bool player::allPokemonsAreDead()
{
	for(unsigned int i = 0; i < nbPokemon; i++)
	{
		if(tabPokemon[i].health > 0) return false;
	}
	return true;
}

void player::changePlacePoke(unsigned int id1, unsigned int id2)
{
	pokemon tempPoke = tabPokemon[id1];

	tabPokemon[id1] = tabPokemon[id2];
	tabPokemon[id2] = tempPoke;
}

bool player::hasFreePokeLocation()
{
	return nbPokemon < NBPLAYERPOKE;
}
