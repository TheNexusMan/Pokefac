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

	/**
	@brief 
	Etabli le nom du personnage
	
	@param name
	@return none
	
	Exemple Code Block / Visual
	@code
	NPC.setName(name);
	@endcode */
	void setName(string name);

	/**
	@brief 
	Etabli la position x et y du personnage
	
	@param x, y
	@return none
	
	Exemple Code Block / Visual
	@code
	NPC.setNewPos(x, y);
	@endcode */
	void setNewPos(unsigned int x, unsigned int y);

	/**
	@brief 
	Etabli la position x du personnage
	
	@param x
	@return none
	
	Exemple Code Block / Visual
	@code
	NPC.setPosX(x);
	@endcode */
	void setPosX(unsigned int x);

	/**
	@brief 
	Etabli la position y du personnage
	
	@param y
	@return none
	
	Exemple Code Block / Visual
	@code
	NPC.setPosY(y);
	@endcode */
	void setPosY(unsigned int y);

	/**
	@brief 
	Renvoie la position x du personnage
	
	@param none
	@return posX
	
	Exemple Code Block / Visual
	@code
	NPC.getPosX();
	@endcode */
	unsigned int getPosX();

	/**
	@brief 
	Renvoie la position y du personnage
	
	@param none
	@return posY
	
	Exemple Code Block / Visual
	@code
	NPC.getPosY();
	@endcode */
	unsigned int getPosY();

	/**
	@brief 
	Etabli la position de la texture du personnage
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	NPC.setIdleTexture();
	@endcode */
	void setIdleTexture();

private:
	unsigned int posX;
	unsigned int posY;
};

#endif