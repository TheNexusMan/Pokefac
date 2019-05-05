#include "character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::setName(string name)
{
	name = name;
}

void Character::setNewPos(unsigned int x, unsigned int y)
{
	posX = x;
	posY = y;
}

void Character::setPosX(unsigned int x)
{
	posX = x;
}

void Character::setPosY(unsigned int y)
{
	posY = y;
}

unsigned int Character::getPosX()
{
	return posX;
}

unsigned int Character::getPosY()
{
	return posY;
}

char Character::getOrientation()
{
	return orientation;
}

void Character::setOrientation(char newOrientation)
{
	orientation = newOrientation;
}