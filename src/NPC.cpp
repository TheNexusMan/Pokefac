#include "NPC.h"



NPC::NPC()
{
}


NPC::~NPC()
{
}


void NPC::setRotation(unsigned int nb)
{
	rotation = nb;
}

int NPC::getRotation()
{
	return rotation;
}


void NPC::checkLine(unsigned int x, unsigned int y, player playerOne)
{
	unsigned int positionX = getPosX();
	unsigned int positionY = getPosY();

	switch (getRotation())
	{
	
		// Nord
	case 1: if ((playerOne.getPosY() == getPosY() - 1 || getPosY() - 2 || getPosY() - 3) && (playerOne.getPosX() == getPosX()))
	{
		//Engage le combat
		break;
	}

		//Est
	case 2:	if ((playerOne.getPosX() == getPosX() + 1 || getPosX() + 2 || getPosX() + 3) && (playerOne.getPosY() == getPosY()))
	{
		//Engage le combat
		break;
	}

		//Sud
	case 3:	if ((playerOne.getPosY() == getPosY() + 1 || getPosY() + 2 || getPosY() + 3) && (playerOne.getPosX() == getPosX()))
	{
		//Engage le combat
		break;
	}
		
		// Ouest
	case 4:if ((playerOne.getPosX() == getPosX() - 1 || getPosX() - 2 || getPosX() - 3) && (playerOne.getPosY() == getPosY()))
	{
		//Engage le combat
		break;	
	}
}
