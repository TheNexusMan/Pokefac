/**
@brief Class World, g�re tout le jeu et les mets en relations

@author pokeFac team
@file world.h
@version 1.0
@date 19/03/2019

*/
#ifndef _WORLD
#define _WORLD

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <cassert>
//#include <SDL.h>
//#include <SDL_image.h>
#include "pokemon.h"
#include "NPC.h"
#include "player.h"
#include "terrain.h"

#include "winTxt.h"

#define DEBUG false

using namespace std;

const unsigned int NBPOKEMON = 3;
const unsigned int NB_NPC = 2;
const unsigned int NB_DOOR = 4; //Toujours un multiple de 2

	struct Door
	{
		unsigned int id;
		unsigned int posX;
		unsigned int posY;
		unsigned int destPosX;
		unsigned int destPosY;
		string terrainNamePos;
		string terrainNameDest;
	};

class world{
public:
	terrain mainTerrain;
	NPC NPCTab[NB_NPC];
	player mainPlayer;
	pokemon pokeTab[NBPOKEMON];
	Door doors[NB_DOOR];

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

	@param mainPlayer
	@return none

	Exemple Code Block / Visual
	@code
	randomCombat(mainPlayer);
	@endcode
	*/
	void randomCombat(player & mainPlayer);

	/**
	@brief
	Retourne true si le d�placement est autoris�, false sinon
	(Si Caract�re = # || N => false else => true)

	@param x, y, mainPlayer
	@return ((x >= 0) && (x < sizeTerrain) && (y >= 0) && (y < sizeTerrain) && (terrain.terrain[x][y] != '#') && (terrain.terrain[x][y] != 'N'))

	Exemple Code Block / Visual
	@code
	moveIsAllowed(10,15);
	@endcode
	*/
	bool moveIsAllowed(player mainPlayer, const int x, const int y) const;

	/**
	@brief
	Verifie si le personnage est dans la ligne d'un NPC

	@param npc, mainPlayer, x, y
	@return none

	Exemple Code Block / Visual
	@code
	isInLine(npc,mainPlayer,x,y);
	@endcode
	*/
	void isInLine(NPC npc, player mainPlayer, const int x, const int y) const;
	
	/**
	@brief
	Initialise le jeu (Fais appel à tous les inits de toutes les classes)

	@param none
	@return none

	Exemple Code Block / Visual
	@code
	initGame();
	@endcode
	*/
	void initGame();

	/**
	@brief
	Initialise toutes les portes via un fichier .txt

	@param none
	@return none

	Exemple Visual
	@code
	world.initDoor();
	@endcode
	*/
	void initDoor();

	/**
	@brief
	Fonction retournant une porte
	Permet de tester sur quelle porte se situe le joueur et de le téléporter ensuite

	@param mainPlayer
	@return returnedDoor

	Exemple Visual
	@code
	world.whichDoor(mainPlayer);
	@endcode
	*/
	Door whichDoor(player mainPlayer);

	/** 
	@brief
	Procedure faisant appel à la fonction whichDoor
	permet de téléporter le joueur dans un nouveau terrain

	@param none
	@return none

	Exemple Visual
	@code
	world.door();
	@endCode
	*/
	void door();

	/** 
	@brief
	Permet de téléporter le joueur

	@param mainPlayer, terrain, x, y
	@return none

	Exemple Visual
	@code
	world.teleport(mainPlayer, terrain, x, y);
	@endCode
	*/
	void teleport(player & mainPlayer, string terrain, unsigned int x, unsigned int y);

private:
	/**
	@brief
	Remplie le tableau de pokemon et leurs caractéristiques en fonction du fichier pokemons.txt
	
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
	Remplie le tableau de NPC et met leurs caractéristiques en fonction d'un fichier txt
	
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
	Verifie si le Joueur est dans les hautes herbes
	True si la position est dans un caract�re 'H'
	false sinon

	@param x, y
	@return (terrain.terrain[x][y] == 'H');

	Exemple Code Block / Visual
	@code
	isInHerb(x, y);
	@endcode
	*/
	bool isInHerb(const int x, const int y) const;

	/**
	@brief
	Lance la boucle de combat

	@param mainPlayer, opponentPoke, isAgainstPokemon
	@return none

	Exemple Code Block / Visual
	@code
	launchBattle(mainPlayer, opponentPoke, true);
	@endcode
	*/
	void launchBattle(player & mainPlayer, pokemon opponentPoke, bool isAgainstPokemon);

	/**
	@brief
	Affiche la vie des deux adversaires

	@param mainPlayer, playerPoke, opponentPoke, isAgainsPokemon
	@return none

	Exemple Code Block / Visual
	@code
	displayOpponentsLife(mainPlayer, playerPoke, opponentPoke, isAgainstPokemon);
	@endcode
	*/
	void displayOpponentsLife(const player mainPlayer, const pokemon playerPoke, const pokemon opponentPoke, const bool isAgainstPokemon) const;

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