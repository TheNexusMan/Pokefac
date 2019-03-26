/**
@brief Class World, gère tout le jeu et mets les autres class en relations

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
#include <sys/stat.h>
#include <ctime>

#include "pokemon.h"
#include "NPC.h"
#include "player.h"
#include "terrain.h"

#include "winTxt.h"

#define DEBUG false

using namespace std;

const unsigned int NBPOKEMON = 10;
const unsigned int NBPLAYERPOKEMON = 6;
const unsigned int NB_NPC = 3;
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
	Player mainPlayer;
	Pokemon pokeTab[NBPOKEMON];
	Door doors[NB_DOOR];
	string gameSaveName;
	bool menuOn;

	/**
	@brief
	Permet de sauvegarder la partie pour la reprendre ultérieurement
	Crée un dossier "saveGame" si inexistant

	@param string saveName
	@return none

	Exemple Visual
	@code
	saveGame("save1");
	@endcode
	 */
	void saveGame(string saveName);

	/**
	@brief
	Permet de charger une partie sauvegardée sur le disque dur (via un .txt)
	Charge les sauvegardes  dans "saveGame"

	@param string saveName
	@return none

	Exemple Visual
	@code
	loadGame("save1");
	@endcode
	*/
	void loadGame(string saveName);

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
	void randomCombat(Player & mainPlayer);

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
	bool moveIsAllowed(Player mainPlayer, const int x, const int y) const;

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
	void isInLine(NPC npc, Player mainPlayer, const int x, const int y) const;
	
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
	Door whichDoor(Player mainPlayer);

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
	void teleport(Player & mainPlayer, string terrain, unsigned int x, unsigned int y);

	/** 
	@brief
	Lance le menu

	@param gameOn
	@return none

	Exemple Visual
	@code
	world.menu(GameOn);
	@endCode
	*/
	void menu(bool & gameOn);

	/** 
	@brief
	Lance le menu des pokémon du joueur

	@param none
	@return none

	Exemple Visual
	@code
	world.menu(win);
	@endCode
	*/
	void displayPokemon();

	/** 
	@brief
	Option d'organisation des pokémon
	Le paramètre pokeMenuOn permet deux choses : lors de l'utilisation de la fonction hors combat, il ferme
	en cascade tous les menus si passé à false. Dans un combat, le paramètre est mis à false pour éviter l'affichage
	de certains choix.

	@param pokeMenuOn
	@return none

	Exemple Visual
	@code
	world.menu(pokeMenuOn);
	@endCode
	*/
	void organisePokemon(bool & pokeMenuOn);

	/**
	@brief
	Verifie si le joueur est sur une case de Soin 
	et soigne ses pokemons

	@param mainPlayer
	@return none

	code Visual
	@end
	world.healAll(mainPlayer);
	@endcode
	 */
	void healAll(Player & mainPlayer);

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
	Vérifie si le joueur est sur une case de vie
	true si la position est des dans un caractere 'V'
	false sinon

	@param x, y
	@return (terrain.terrain[x][y] == 'V')

	Exemple Visual
	@code
	isOnHeal(2, 4);
	@endcode
	 */
	bool isOnHeal(const int x, const int y) const;

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
	void launchBattle(Player & mainPlayer, Pokemon opponentPoke, bool isAgainstPokemon);

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
	void displayOpponentsLife(const Player mainPlayer, const Pokemon PlayerPoke, const Pokemon opponentPoke, const bool isAgainstPokemon) const;

	//Fonctions de DEBUG (Affiche dans la console pour SDL)

	/**
	@brief
	Prévient dans les logs du lancement du programme
	Affiche des informations supl�mentaires � l'utilisateur

	@param none
	@return none

	Exemple Code Block / Visual
	@code
	debugWarning();
	@endcode
	*/
	void logFilesStart() const;
};

#endif