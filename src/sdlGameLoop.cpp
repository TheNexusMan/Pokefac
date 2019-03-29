#include "sdlGameLoop.h"


const int TAILLE_SPRITE = 32;

float temps()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC; //Conversion des ms en secondes
}

// ======================================= CLASS IMAGE ===================================  //

Image::Image()
{
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

void Image::loadFromFile(const char* filename, SDL_Renderer * renderer)
{
    surface = IMG_Load(filename);
    if(surface == NULL)
    {
        string nfn = string("../") + filename;
        cout << "Error : Impossible de lire " << filename << ". Tentative de lecture de : " << nfn << endl;
        surface = IMG_Load(nfn.c_str());
        if(surface == NULL)
        {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if(surface == NULL)
    {
        cout << "Error : Impossible de lire " << filename << endl;
        exit(1);
    }
    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
    {
        cout << "Error : Probleme lors de la création de la texture provenant de : " << filename << endl;
        exit(1);
    }

}

void Image::loadFromCurrentSurface(SDL_Renderer * renderer)
{
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
    {
        cout << "Error : Probleme lors de la création de la texture provenant de la surface" << endl;
        exit(1);
    }
}

void Image::draw(SDL_Renderer * renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if(has_changed)
    {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels, surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }
    ok = SDL_RenderCopy(renderer, texture, NULL, &r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const 
{
    return texture;
}
void Image::setSurface(SDL_Surface * surf)
{
    surface = surf;
}

// ======================================= CLASS SDLJEU ===================================  //


SdlGame::SdlGame()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if(TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initalisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image impossible a initialisé, SDL_image error : " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048) < 0)
    {
        cout << "SDL_mixer impossible a initialisé, SDL_mixer error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        withSound = false;
    } else withSound = false;

    int dimx, dimy;
    dimx = SIZETERRAIN * TAILLE_SPRITE;
    dimy = SIZETERRAIN * TAILLE_SPRITE;

    //Creation de la fenetre
    window = SDL_CreateWindow("PokeFac", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == NULL)
    {
        cout << "Erreur lors de la création de la fenetre ! Erreur SDL : " << SDL_GetError() <<  endl;
        SDL_Quit();
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Ajout ici du chargement des images
    im_Tree.loadFromFile("./data/textures/tree.png", renderer);
    im_GrassLand.loadFromFile("./data/textures/grass03.png", renderer);
    im_herbs.loadFromFile("./data/textures/grass.png", renderer);
    im_MissingTexture.loadFromFile("./data/textures/error.png", renderer);

    //fin de l'ajout du chargement des images


    //Texte
    /*
    font == TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if(font == NULL)
    {
        cout << "Failed to load the font SDL_TTF : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    font_color.r = 50; 
    font_color.g = 50;
    font_color.b = 255;
    font_im.setSurface(TTF_RenderText_Solid(fond, "Pokefac", font_color));
    font_im.loadFromCurrentSurface(render);
    */

   // Sounds
   if(withSound)
   {
       sound = Mix_LoadWAV("PATH");
       if(sound == NULL)
       {
           cout << "Failed to load son.wave ! SDL_mixer Error : " << Mix_GetError() << endl;
           SDL_Quit();
           exit(1);

       }
   }
}

SdlGame::~SdlGame()
{
    if(withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SdlGame::sdlDisplay(world world)
{
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);


    int dimx, dimy;
    dimx = SIZETERRAIN * TAILLE_SPRITE;
    dimy = SIZETERRAIN * TAILLE_SPRITE;
    im_MissingTexture.draw(renderer, 0,0,dimx,dimy);
    for(unsigned int x = 0; x < SIZETERRAIN; x++)
    {
        for(unsigned int y = 0; y < SIZETERRAIN; y++)
        {
            if(world.mainTerrain.terrainTab[y][x] == '#')
            {
                im_Tree.draw(renderer, x*TAILLE_SPRITE, y*TAILLE_SPRITE, TAILLE_SPRITE+10, TAILLE_SPRITE+10);
            }
            if(world.mainTerrain.terrainTab[y][x] == '.')
            {
                im_GrassLand.draw(renderer, x*TAILLE_SPRITE, y*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            }
            if(world.mainTerrain.terrainTab[y][x] == 'H')
            {
                im_herbs.draw(renderer, x*TAILLE_SPRITE, y*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            }
            if((world.mainTerrain.terrainTab[y][x] == 'O') || (world.mainTerrain.terrainTab[y][x] == 'N') || (world.mainTerrain.terrainTab[y][x] == 'V'))
            {
                im_MissingTexture.draw(renderer, x*TAILLE_SPRITE, y*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            }
        }
    }
    im_Tree.draw(renderer, world.mainPlayer.getPosX()* TAILLE_SPRITE, world.mainPlayer.getPosY()* TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    //im_Player.draw(renderer, world.mainPlayer.getPosX()*TAILLE_SPRITE, world.mainPlayer.getPosY()* TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
}

void SdlGame::sdlLoop(world & world)
{
    SDL_Event events;
    bool quit = false;
    bool hasMoved = false;

    //Uint32 t = SDL_GetTicks(), nt;

    while(!quit)
    {

        if(hasMoved)
		{
			world.randomCombat(world.mainPlayer);
			world.healAll(world.mainPlayer);
			
			hasMoved = false;
		}
        while(SDL_PollEvent(&events))
        {
            if(events.type == SDL_QUIT) quit = true;
            else if (events.type == SDL_KEYDOWN)
            {
                switch(events.key.keysym.scancode)
                {
                    case SDL_SCANCODE_UP: if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosY()-1, world.mainPlayer.getPosX()))
                                            {
                                                world.mainPlayer.moveLeft();
                                                cout << world.mainPlayer.getPosX() << " " << world.mainPlayer.getPosY() << endl;
                                                hasMoved = true;
                                            }
                                            break;
                    case SDL_SCANCODE_LEFT: if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosY(), world.mainPlayer.getPosX()-1))
                                            {
                                                world.mainPlayer.moveUp();
                                                cout << world.mainPlayer.getPosX() << " " << world.mainPlayer.getPosY() << endl;
                                                hasMoved = true;
                                            }
                                            break;
                    case SDL_SCANCODE_DOWN: if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosY()+1, world.mainPlayer.getPosX()))
                                            {
                                                world.mainPlayer.moveRight();
                                                cout << world.mainPlayer.getPosX() << " " << world.mainPlayer.getPosY() << endl;
                                                hasMoved = true;
                                            }
                                            break;
                    case SDL_SCANCODE_RIGHT:if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosY(), world.mainPlayer.getPosX()+1))
                                            {
                                                world.mainPlayer.moveDown();
                                                cout << world.mainPlayer.getPosX() << " " << world.mainPlayer.getPosY() << endl;
                                                hasMoved = true;
                                            }
                                            break;
                    case SDL_SCANCODE_X: quit=true;
                                         break;
                    default : break;
                    
                }
                world.door();

            }

        }
        sdlDisplay(world);
        SDL_RenderPresent(renderer);
    }
}