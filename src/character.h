/**
@brief Class Character, contient les fonctions et données relatives aux character

@author pokeFac team
@file character.h
@version 1.0
@date 19/03/2019

*/
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <iostream>
#include <string>
//#include "CharacterTexture.h"

using namespace std;

//! \brief Classé héritée par Player.h et NPC.h
class Character
{
public:
	Character();
	~Character();

	string name;
	
	//CharacterTexture texture;

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
	Retourne l'orientation du personnage (n = Nord, s = Sud, e = Est, o = Ouest)
	
	@param none
	@return orientation
	
	Exemple Code Block / Visual
	@code
	NPC.getOrientation();
	@endcode */
	char getOrientation();

	/**
	@brief 
	Modifie l'orientation du personnage avec une nouvelle orientation
	
	@param newOrientation
	@return none
	
	Exemple Code Block / Visual
	@code
	NPC.setOrientation('n');
	@endcode */
	void setOrientation(char newOrientation);

private:
	char orientation;
	unsigned int posX;
	unsigned int posY;
};

#endif