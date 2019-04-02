#ifndef _SDLGAMELOOP_H
#define _SDLGAMELOOP_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

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
        SDL_Color font_color;

        Mix_Chunk * sound;
        bool withSound;

    //Rajouter les images a charger ici
    Image im_Tree;
    Image im_GrassLand;
    Image im_herbs;
    Image im_MissingTexture;
    //Fin de rajout des images a charger

    public:
        SdlGame();
        ~SdlGame();
        void sdlLoop(world & world);
        void sdlDisplay(world world);

};
#endif

