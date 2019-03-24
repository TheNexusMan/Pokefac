#ifndef PLAYER_H
#define PLAYER_H 

#include "character.h"
#include "pokemon.h"
//#include "object.h"
//#include "dynamicClassTab.h" 
//#include "badge.h"
#include <iostream>

using namespace std;

const int MAXB = 5;
const int NBPLAYERPOKE = 6;

class player : public character
{
private:

	unsigned int money;
//	badge tab[MAXB];
	unsigned int pokeball;
//	dynamicClassTab object[];

public:
	pokemon tabPokemon[NBPLAYERPOKE];
	unsigned int nbPokemon;

	void moveUp();
	void moveDown();
	void moveLeft();
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
	Initialise les caract�ristiques de bases du player
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	initPlayer();
	//Definie la position / argent et nb pokeballs
	@endcode */
	void initPlayer(const pokemon poke);
		
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
	mainPlayer.getPokeball();
	@endcode */
	unsigned int getPokeball();

	/**
	@brief 
	Ajoute le pokemon passé en paramètre
	
	@param poke
	@return none
	
	Exemple Code Block / Visual
	@code
	mainPlayer.addPokemon(poke);
	@endcode */
	void addPokemon(const pokemon & poke);

	/**
	@brief 
	Renvoie un pokémon par référence en fonction de l'id passé en paramètre
	
	@param id
	@return pokemon&
	
	Exemple Code Block / Visual
	@code
	mainPlayer.getPokemon(1);
	@endcode */
	pokemon& getPokemon(unsigned int id);

	/**
	@brief 
	Renvoie un pokémon par en donnée en fonction de l'id passé en paramètre
	
	@param id
	@return pokemon&
	
	Exemple Code Block / Visual
	@code
	mainPlayer.getPokemon(1);
	@endcode */
	pokemon getPokemon(unsigned int id) const;

	/**
	@brief 
	Ehange le pokémon mort au combat par le premier vivant du tableau
	
	@param none
	@return none
	
	Exemple Code Block / Visual
	@code
	mainPlayer.replaceDeadPokemon();
	@endcode */
	void replaceDeadPokemon();

	/**
	@brief 
	Ehange les emplacements des pokémons en id1 et id2
	
	@param id1, id2
	@return none
	
	Exemple Code Block / Visual
	@code
	mainPlayer.changePlacePoke(0, 5);
	@endcode */
	void changePlacePoke(unsigned int id1, unsigned int id2);

	/**
	@brief 
	Renvoie vrai si le pokemon passé en paramètre est déjà possédé par le joueur
	
	@param poke
	@return bool
	
	Exemple Code Block / Visual
	@code
	mainPlayer.hasThisPokemon(poke);
	@endcode */
	bool hasThisPokemon(const pokemon & poke);

	/**
	@brief 
	Renvoie vrai si le joueur a encore de la place pour un pokémon
	
	@param none
	@return bool
	
	Exemple Code Block / Visual
	@code
	mainPlayer.hasFreePokeLocation();
	@endcode */
	bool hasFreePokeLocation();
};

#endif