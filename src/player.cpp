#include "player.h"

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
	setNewPos(10, 7); //Place le joueur aux coordonnées (10,7)
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


/*
void player::moveUp()
{
	posY = getPosY();
	if (posY == 0) posY = posY;
	else posY = posY - 1; 
}

void player::moveDown()
{
	posY = getPosY();
	if (posY == dimY) posY = posY;
	else posY = posY + 1;
}

void player::moveLeft()
{
	posX = getPosX();
	if (posX == 0) posX = posX;
	else posX = posX - 1;
}

void player::moveRight()
{
	posX = getPosX;
	if (posX == dimY) posX = posX;
	else posX = posX + 1;
}
*/