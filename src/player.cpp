#include "player.h"

void Player::moveUp()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x-1, y);
}

void Player::moveDown()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x + 1, y);
}

void Player::moveLeft()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x, y-1);
}

void Player::moveRight()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x, y+ 1);
}

unsigned int Player::getMoney()
{
	return money;
}

void Player::addMoney(unsigned int adding)
{
	money += adding;
}

void Player::initPlayer(const Pokemon poke)
{	
	setPosX(1);
	setPosY(2); //Place le joueur aux coordonnées (1,2)
	addMoney(100); //Lui donne 100 en Argent
	setPokeball(5); // Lui donne 5 pokeballs
	tabPokemon[0] = poke;
	nbPokemon = 1;
}

void Player::setPokeball(int nb)
{
	pokeball += nb;
}

unsigned int Player::getPokeball()
{
	return pokeball;
}

void Player::addPokemon(const Pokemon & poke)
{
	if(hasFreePokeLocation() && !hasThisPokemon(poke))
	{
		tabPokemon[nbPokemon] = poke;
		nbPokemon++;
	}
}

Pokemon& Player::getPokemon(unsigned int id)
{
	return tabPokemon[id];
}

Pokemon Player::getPokemon(unsigned int id) const
{
	return tabPokemon[id];
}

bool Player::hasThisPokemon(const Pokemon & poke)
{
	for(unsigned int i = 0; i < nbPokemon; i++)
	{
		if(tabPokemon[i].id == poke.id) return true;
	}
	return false;
}

Pokemon& Player::firstPokemonAlive()
{
	unsigned int idPokeAlive = 0;
	while(tabPokemon[idPokeAlive].health <= 0)
	{
		idPokeAlive++;
	}

	return tabPokemon[idPokeAlive];
}

void Player::treatAllPokemon()
{
	for(unsigned int i = 0; i < nbPokemon; i++)
	{
		tabPokemon[i].health = tabPokemon[i].maxHealth;
	}
}

bool Player::allPokemonsAreDead()
{
	for(unsigned int i = 0; i < nbPokemon; i++)
	{
		if(tabPokemon[i].health > 0) return false;
	}
	return true;
}

void Player::changePlacePoke(unsigned int id1, unsigned int id2)
{
	Pokemon tempPoke = tabPokemon[id1];

	tabPokemon[id1] = tabPokemon[id2];
	tabPokemon[id2] = tempPoke;
}

bool Player::hasFreePokeLocation()
{
	return nbPokemon < NBPLAYERPOKE;
}
