#pragma once

#include <iostream>
#include <string>
//#include "characterTexture.h"

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
	void setPos(int x, int y);
	int getPosX();
	int getPosY();
	void setIdleTexture();


};
