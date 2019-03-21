#include "player.h"

#include <math.h>
#include <iostream>




unsigned int player::getMoney()
{
	return money;
}

void player::addMoney(unsigned int adding)
{
	money = money + adding;
}

void player::initPlayer()
{
	posX = 10;
	posY = 7;  //Place le joueur aux coordonnées (10,7)
	addMoney(100); //Lui donne 100 en Argent
	setPokeball(5); // Lui donne 5 pokeballs
}

void player::setPokeball(int nb)
{
	pokeball += nb;
}

unsigned int player::getPokeball()
{
	return pokeball;
}



void player::moveUp()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x - 1, y);
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
	setNewPos(x, y - 1);
}

void player::moveRight()
{
	unsigned int x = getPosX();
	unsigned int y = getPosY();
	setNewPos(x, y + 1);
}