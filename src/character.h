#ifndef _CHARACTER_H
#define _CHARACTER_H

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
	//characterTexture texture;

	void setName(string name);
	void setNewPos(unsigned int x, unsigned int y);
	void setPosX(unsigned int x);
	void setPosY(unsigned int y);
	unsigned int getPosX();
	unsigned int getPosY();
	void setIdleTexture();

private:
	unsigned int posX;
	unsigned int posY;
};

#endif