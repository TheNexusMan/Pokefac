#include "player.h"

unsigned int player::getMoney()
{
	return money;
}

void player::addMoney(unsigned int adding)
{
	money = money + adding;
}

void player::initPosition()
{
	setPos(dimX/2, dimY/2);
}

void player::moveUp()
{
	posY = getPosY;
	if (posY == 0) posY = posY;
	else posY = posY - 1; 
}

void player::moveDown()
{
	posY = getPosY;
	if (posY == dimY) posY = posY;
	else posY = posY + 1;
}

void player::moveLeft()
{
	posX = getPosX;
	if (posX == 0) posX = posX;
	else posX = posX - 1;
}

void player::moveLeft()
{
	posX = getPosX;
	if (posX == dimY) posX = posX;
	else posX = posX + 1;
}
