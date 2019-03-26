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

void character::setNewPos(unsigned int x, unsigned int y)
{
	posX = x;
	posY = y;
}

void character::setPosX(unsigned int x)
{
	posX = x;
}

void character::setPosY(unsigned int y)
{
	posY = y;
}

void character::setIdleTexture()
{
	// A definir
}

unsigned int character::getPosX()
{
	return posX;
}

unsigned int character::getPosY()
{
	return posY;
}