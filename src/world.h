/**
@brief Class World, g�re tout le jeu et les mets en relations

@author pokeFac team
@file world.h
@version 1.0
@date 19/03/2019

*/
#ifndef _WORLD_H
#define _WORLD_H

#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "pokemon.h"
#include "NPC.h"
#include "player.h"
#include "terrain.h"
#include <cassert>

#define DEBUG false

using namespace std;

const unsigned int NBPOKEMON = 3;
const unsigned int NB_NPC = 3;


class world{
public:
	terrain terrain;
	NPC NPCTab[NB_NPC];
	player mainPlayer;
	pokemon poke[NBPOKEMON];

	


	/**
	@brief
	Constructeur de la classe world
	
	@param none
	@return none

	Exemple Code Block / Visual
	@code
	world world;
	@endcode
	*/
	world();
	
	/**
	@brief
	Retourne un nombre al�atoire entre 0 et 100

	@param none
	@return rand()%100;

	Exemple Code Block / Visual
	@code
	randomNumber();
	@endcode
	*/
	int randomNumber();
	/**
	@brief
	Lance un combat al�atoire en fonction de la position (Hautes herbes ou non)


	@param playerOne
	@return none

	Exemple Code Block / Visual
	@code
	randomCombat(playerOne);
	@endcode
	*/
	void randomCombat(player playerOne);

	/**
	@brief
	Retourne true si le d�placement est autoris�, false sinon
	(Si Caract�re = # || N => false else => true)


	@param x, y, playerOne
	@return ((x >= 0) && (x < sizeTerrain) && (y >= 0) && (y < sizeTerrain) && (terrain.terrain[x][y] != '#') && (terrain.terrain[x][y] != 'N'))

	Exemple Code Block / Visual
	@code
	moveIsAllowed(10,15);
	@endcode
	*/
	bool moveIsAllowed(player playerOne, const int x, const int y) const;

	/**
	@brief
	Verifie si le personnage est dans la ligne d'un NPC

	@param npc, playerOne, x, y
	@return none

	Exemple Code Block / Visual
	@code
	isInLine(npc,playerOne,x,y);
	@endcode
	*/
	void isInLine(NPC npc, player playerOne, const int x, const int y) const;
	

	
	/**
	@brief
	Initialise le jeu (Fais appel � tous les inits de toutes les classes)

	@param npc
	@return none

	Exemple Code Block / Visual
	@code
	initGame(npc);
	@endcode
	*/
	void initGame(NPC npc);

private:
	/**
	@brief
	Remplie le tableau de pokemon et met leurs caract�ristiques en fonction d'un fichier txt
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	initPokeTab();
	@endcode
	*/
	void initPokeTab();

	/**
	@brief
	Remplie le tableau de NPC et met leurs caract�ristiques en fonction d'un fichier txt
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	initNpcTab();
	@endcode
	*/
	void initNPCTab();



	/**
	@brief
	Initialise le personnage joueur
	@param player playerOne
	@return none

	Exemple Code Block / Visual
	@code
	initPlayer(mainPlayer);
	@endcode	
	*/
	void initPlayer(player playerOne); // Remplira toutes les caract�ristiques du joueurs
									   // Position && Nom ...


	/**
	@brief
	Verifie si le Joueur est dans les hautes herbes
	True si la position est dans un caract�re 'H'
	false sinon

	@param playerOne, x, y
	@return (terrain.terrain[x][y] == 'H');

	Exemple Code Block / Visual
	@code
	isInHerb(playerOne, x, y);
	@endcode
	*/
	bool isInHerb(player playerOne, const int x, const int y) const;

	//Fonctions de DEBUG (Affiche dans la console pour SDL)
	/**
	@brief
	Affiche des '*' pour le DEBUG, donne des informations supl�mentaires

	@param none
	@return none

	Exemple Code Block / Visual
	@code
	displayStars();
	@endcode
	*/
	void displayStars() const;
	/**
	@brief
	Pr�vient dans la console que le mode DEBUG est activ�
	Affiche des informations supl�mentaires � l'utilisateur

	@param none
	@return none

	Exemple Code Block / Visual
	@code
	debugWarning();
	@endcode
	*/
	void debugWarning() const;

};

#endif