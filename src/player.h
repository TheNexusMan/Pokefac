#ifndef PLAYER_H
#define PLAYER_H 

#include "character.h"
#include "terrain.h"
#include "pokemon.h"
//#include "object.h"
//#include "dynamicClassTab.h" 
//#include "badge.h"

#include <iostream>
using namespace std;

const int MAXB = 5;

class player : public character
{
private:

	unsigned int money;
//	badge tab[MAXB];
	unsigned int pokeball = 0;
//	pokemon nbPokemon[];
//	dynamicClassTab object[];

public:
	

	/**
	@brief
	Deplace le joueur vers le haut

	@param none
	@return none

	Exemple Visual Studio
	@code
	player.moveUp();
	@endcode*/
	void moveUp();

	/**
	@brief
	Deplace le joueur vers le bas

	@param none
	@return none

	Exemple Visual Studio
	@code
	player.moveDown();
	@endcode*/
	void moveDown();


	/**
	@brief
	Deplace le joueur vers la gauche

	@param none
	@return none

	Exemple Visual Studio
	@code
	player.moveLeft();
	@endcode*/
	void moveLeft();


	/** 
	@brief
	Deplace le joueur vers la droite
	
	@param none
	@return none
	
	Exemple Visual Studio
	@code
	player.moveRight();
	@endcode*/
	void moveRight();




	/**
	@brief
	Ajoute de l'argent au player
	
	@param int adding
	@return none
	Exemple Code Block / Visual
	@code
	player.addMoney(10)
	//Ajoute 10 en argent au joueur
	@endcode */
	void addMoney(unsigned int adding);

	/** 
	@brief
	Recupere l'argent du joueur
	
	@param none
	@return unsigned int money
	Exemple Code Block / Visual
	@code
	player.getMoney();
	@endcode */
	unsigned int getMoney();

	/**
	@brief
	Initialise les caractéristiques de bases du player
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	initPlayer();
	//Definie la position / argent et nb pokeballs
	@endcode */
	void initPlayer();
		
	/**
	@brief
	Permet de definir le nombre de pokeballs (fais un somme)
	
	@param nb
	@return none
	
	Exemple Code Block / Visual
	@code
	setPokeball(5);
	//Fais pokeball += 5
	@endcode */
	void setPokeball(int nb);

	/**
	@brief 
	Retourne le nombre de pokeballs actuelles
	
	@param none
	@return pokeball
	
	Exemple Code Block / Visual
	@code
	playerOne.getPokeball();
	@endcode */
	unsigned int getPokeball();
};

#endif