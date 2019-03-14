#include "character.h"


character::character()
{
}


character::~character()
{
}

void character::setName(string name)
{
	name = name;
}

void character::setPos(int x, int y)
{
	posX = x;
	posY = y;
}

void character::setIdleTexture()
{
	// A definir
}

int character::getPosX()
{
	return posX;
}

int character::getPosY()
{
	return posY;
}