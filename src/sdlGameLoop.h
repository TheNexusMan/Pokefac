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



class Image {
    private: 
        SDL_Surface * surface;
        SDL_Texture * texture;
        bool has_changed;
    public:
        Image();
        void loadFromFile(const char* fileName, SDL_Renderer * renderer);
        void loadFromCurrentSurface(SDL_Renderer * renderer);
        void draw(SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
        SDL_Texture * getTexture() const;
        void setSurface(SDL_Surface * surf);
};

class SdlGame
{
    private:
        world mainWorld;
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
        
        Image font_pokemonName;
        Image font_pokemonHP;

        SDL_Color font_color;

        Mix_Chunk * sound;
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

    //Pokemons
    Image im_linuchu;
    //Fin de rajout des images a charger

    int frameSize, textureWidth, textureHeight;
    SDL_Texture *playerSpriteTexture;
    SDL_Rect playerRect;
    SDL_Rect playerPosition;

    public:
        SdlGame();
        ~SdlGame();
        void sdlLoop(world & world);
        void sdlDisplayMenu();
        void sdlDisplayAllWorld(world world);
        void sdlLaunchAnimation(world world, char direction);
        void sdlDisplay(world world, int tileX, int tileY);

        void sdlDisplayBattle(Uint32 &deltaTime, Uint32 &elapsedTime, bool dresseur);
        void sdlDisplayChatBox(world world);



        void sdlDisplayGameSaved(Uint32 &deltaTime, Uint32 &elapsedTime, world &world);
        void sdlDisplayGameLoaded(Uint32 &deltaTime, Uint32 &elapsedTime, world &world);
        
        void sdlDisplayPokemonMenu(world world, bool inBattle);

};
#endif

