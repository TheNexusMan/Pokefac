#ifndef PLAYER_H
#define PLAYER_H 

#include "character.h"
#include "pokemon.h"
//#include "object.h"
//#include "dynamicClassTab.h" 
#include <math.h>
#include <iostream>

using namespace std;

const unsigned int MAXB = 5;

struct badge{
	string name, championName;	
};

class player : character
{
private:

	unsigned int money;
	badge tab[MAXB];
	unsigned int pokeball;
	pokemon nbPokemon[];
	//dynamicClassTab object[];

public:
	
	player();
	~player();
	unsigned int player::getMoney();
	void player::addMoney(unsigned int adding);
	void initPosition();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();	
};

#endif