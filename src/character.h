#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <iostream>
#include <string>
#include "characterTexture.h"

using namespace std;

class character
{
public:
	character();
	~character();


	string name;
	unsigned int posX;
	unsigned int posY;
	characterTexture texture;

	void setName(string name);
	int getPosX();
	int getPosY();
	void setIdleTexture();
	void setNewPos(unsigned int x, unsigned int y);


};
#endif