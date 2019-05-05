/**
@brief Class SdlGameLoop, Gère tout l'affichage du SDL

@author pokeFac team
@file sdlGameLoop.h
@version 1.0
@date 19/03/2019

*/


#ifndef _SDLGAMELOOP_H
#define _SDLGAMELOOP_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cassert>
using namespace std;

#include "world.h"


//! \brief Classe pour le SDL
class Image {
    private: 
        SDL_Surface * surface;
        SDL_Texture * texture;
        bool has_changed;
    public:
        Image();
    	/**
        @brief
        Charge une image en fonction d'un fichier

        @param const chat* filename, SDL_Renderer * renderer
        @return none
        */
        void loadFromFile(const char* fileName, SDL_Renderer * renderer);
        void loadFromCurrentSurface(SDL_Renderer * renderer);
        /**
        @brief
        Dessine l'image dans la fênetre aux coordonnées choises

        @param SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1
        @return none
        */
        void draw(SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
        SDL_Texture * getTexture() const;
        void setSurface(SDL_Surface * surf);
};

//! \brief Structure de gestion des combats
struct Battle{
    bool isInBattle;
	bool isAgainstNPC;
    bool oppLifeHasChanged;
    bool playerLifeHasChanged;
    bool endTurn;
    bool firstTurn;
	NPC * NPCInFight;
	Pokemon pokeInFight;
};
//! \brief Structure de gestion du Menu
struct Menu{
    bool organizePoke;
	bool isTaken;
    bool isModified;
    unsigned int indice;
    unsigned int idPokeInfo;
};
//! \brief Classe gérant tout ce qui touche l'affichage SDL
class SdlGame
{
private:
    SDL_Window * window;
    SDL_Renderer * renderer;

    TTF_Font * font;
    Image font_im;
    Image font_menuPoke;
    Image font_menuSave;
    Image font_menuLoad;
    Image font_menuQuit;
    Image font_chatBox;
    Image font_chatPokeGo;

    Image font_gameSaved;
    Image font_gameLoaded;


    Image font_choosePoke;
    
    Image font_pokemonName[NBPLAYERPOKE];
    Image font_pokemonNameInfo;
    Image font_pokemonHP[NBPLAYERPOKE];
    Image font_pokemonTitleNPC;
    Image font_pokemonHPNPC;
    Image font_pokemonHPPlayer;

    //For display Info
    Image font_pokemonTypeTitle;
    Image font_pokemonType;
    Image font_pokemonAttacksTitle;
    Image font_pokemonDamagesTitle;
    Image font_pokemonAttacks[4];
    Image font_pokemonDamages[4];
    Image font_sentence;
    Image font_sentence2;
    Image font_fuite;


    SDL_Color font_color;
    SDL_Color font_red;
    SDL_Color font_green;

    Mix_Music * sound;
    Mix_Music * battle;
    Mix_Chunk * footstep;
    bool withSound;

    //Rajouter les images a charger ici
    Image im_Tree;
    Image im_GrassLand;
    Image im_herbs;
    Image im_MissingTexture;
    Image im_chatBox;
    Image im_battleBG;
    Image im_sandRoad;
    Image im_PlayerImage;
    Image im_arena;
    Image im_House;
    Image im_Wood;
    Image im_Arrow;
    Image im_Life;
    Image im_NPCMan;
    Image im_NPCWoman;

    //Pokemons


    Image im_PokeBattle;
    Image im_PokeBattleOpp;
    //Fin de rajout des images a charger

    int frameSize, textureWidth, textureHeight;
    SDL_Texture *playerSpriteTexture;
    SDL_Rect playerRect;
    SDL_Rect playerPosition;

    Battle infosBattle;
    Menu infosMenu;

    public:
    	/**
        @brief
        Constructeur de la classe SDLGame, initilise les librairies SDL

        @param none
        @return none
        */
        SdlGame();
    	/**
        @brief
        Destructeur de la classe SDLGame

        @param none
        @return none
        */
        ~SdlGame();
    	/**
        @brief
        Boucle d'évenement du jeu

        @param world & worlds
        @return none

        Exemple Visual
        @code
        sdlLoop(mainWorld);
        @endcode
        */
        void sdlLoop(world & world);
    	/**
        @brief
        Génere l'affichage du menu pause (touche M)

        @param none
        @return none

        Exemple Visual
        @code
        SdlDisplayMenu();
        @endcode
        */
        void sdlDisplayMenu();
    	/**
        @brief
        Gère l'animation du joueur lors d'un déplacement

        @param world world, char direction
        @return none

        */
        void sdlLaunchAnimation(world world, char direction);
    	/**
        @brief
        Génere l'affichage du terrain

        @param world world, int tileX, int tileY
        @return none

        Exemple Visual
        @code
        SdlDisplay(world, 15, 2);
        @endcode
        */
        void sdlDisplay(world world, int tileX, int tileY);

    	/**
        @brief
        Affiche les points de vie du pokemon adverse

        @param world world
        @return none
        */
        void sdlDisplayBattleOpponentLife(world world);
    	/**
        @brief
        Affiche les points de vie du pokemon du joueur

        @param Pokemon playerPoke
        @return none
        */
        void sdlDisplayBattlePlayerLife(Pokemon playerPoke);
    	/**
        @brief
        Affiche une phrase lors d'un combat

        @param string sentence, string sentence2 = ""
        @return none
        */
        void sdlDisplayBattleSentence(string sentence, string sentence2 = "");
    	/**
        @brief
        Gère le combat entre un joueur et un pokemon/dresseur

        @param world &world, unsigned int action
        @return none
        */
        void sdlDisplayBattle(world & world, unsigned int action);
    	/**
        @brief
        Affiche une barre de dialogue

        @param world world
        @return none
        */
        void sdlDisplayChatBox(world world);


    	/**
        @brief
        Sauvegarde la partie et affiche un message

        @param Uint32 &deltaTime, Uint32 &elapsedTime, world & world
        @return none
        */
        void sdlDisplayGameSaved(Uint32 &deltaTime, Uint32 &elapsedTime,world &world);
    	/**
        @brief
        Charge la partie et affiche un message

        @param Uint32 &deltaTime, Uint32 &elapsedTime, world & world
        @return none
        */
        void sdlDisplayGameLoaded(Uint32 &deltaTime, Uint32 &elapsedTime,world &world);
        
        /**
        @brief
        Affiche le menu pokemon (Touche M -> 1)

        @param world & world, bool inBattle
        @return none
        */
        void sdlDisplayPokemonMenu(world &worl);
        /**
        @brief
        Affiche les infos du pokémon sélectionné (Touche M -> 1 -> (1 à 6))

        @param world &world, int idPoke
        @return none
        */
        void sdlDisplayPokemonInfos(world &world);

    	/**
        @brief
        Lance un combat aléatoire en fonction de la position dans les hautes herbes

        @param world & world
        @return none
        */
        void sdlLaunchRandomCombat(world & world);

        /**
        @brief
        Lance un combat contre le NPC correspondant à la case où se positionne le joueur

        @param world & world
        @return none
        */
        void sdlLaunchNPCBattle(world & world);

        /**
        @brief
        Initialise les informations de la strucure Battle

        @param none
        @return none
        */
        void initInfosBattle();

        /**
        @brief
        Initialise les informations de la strucure Menu

        @param none
        @return none
        */
        void initInfosMenu();

        /**
        @brief
        Interragir avec l'élément devant le joueur

        @param world
        @return none
        */
        void interaction(world & world);

};
#endif

