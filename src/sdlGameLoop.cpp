#include "sdlGameLoop.h"


const int TAILLE_SPRITE = 71;

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
    //dimx = SIZETERRAIN * TAILLE_SPRITE;
    //dimy = SIZETERRAIN * TAILLE_SPRITE;
    dimx = 9 * TAILLE_SPRITE;
    dimy = 9 * TAILLE_SPRITE;

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
    im_GrassLand.loadFromFile("./data/textures/grass03_light.jpg", renderer);
    im_herbs.loadFromFile("./data/textures/grass.png", renderer);
    im_MissingTexture.loadFromFile("./data/textures/error.png", renderer);
    im_chatBox.loadFromFile("./data/textures/chatbox.png", renderer);
    im_PlayerImage.loadFromFile("./data/textures/playerSprite.png", renderer);
    //fin de l'ajout du chargement des images


    //Chargement des texture et données pour l'affichage du joueur
    playerPosition.x = 4*TAILLE_SPRITE+5; //position de l'affichage du joueur
    playerPosition.y = 4*TAILLE_SPRITE-2;
    SDL_QueryTexture(im_PlayerImage.getTexture(), NULL, NULL, &textureWidth, &textureHeight);
    frameSize = textureWidth / 4;
    playerPosition.w = playerPosition.h = frameSize;
    playerRect.x = playerRect.y = 0;
    playerRect.w = playerRect.h = frameSize;


    //Texte
    
    font = TTF_OpenFont("./data/font/pokemon_pixel_font.ttf",50);
    if(font == NULL)
    {
        cout << "Failed to load the font SDL_TTF : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    font_color.r = 0; 
    font_color.g = 0;
    font_color.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font, "Pokefac", font_color));
    font_im.loadFromCurrentSurface(renderer);
    font_menuPoke.setSurface(TTF_RenderText_Solid(font, "1- Pokemons", font_color));
    font_menuPoke.loadFromCurrentSurface(renderer);

    font_menuSave.setSurface(TTF_RenderText_Solid(font, "2- Sauvegarder", font_color));
    font_menuSave.loadFromCurrentSurface(renderer);

    font_menuLoad.setSurface(TTF_RenderText_Solid(font, "3- Charger", font_color));
    font_menuLoad.loadFromCurrentSurface(renderer);

    font_menuQuit.setSurface(TTF_RenderText_Solid(font, "4- Quitter", font_color));
    font_menuQuit.loadFromCurrentSurface(renderer);

    

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

void SdlGame::sdlDisplayAllWorld(world world)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);




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
    im_Tree.draw(renderer, world.mainPlayer.getPosY()* TAILLE_SPRITE, world.mainPlayer.getPosX()* TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    //im_Player.draw(renderer, world.mainPlayer.getPosX()*TAILLE_SPRITE, world.mainPlayer.getPosY()* TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

}

void SdlGame::sdlLaunchAnimation(world world, char direction)
{
    int tileX, tileY;
    unsigned int refresh = 0;
    playerRect.x = 0;
    
    switch (direction)
    {
        case 'u':
            tileX = 0;
            tileY = 0;
            playerRect.y = 3*frameSize;
            while(tileY < TAILLE_SPRITE)
            {
                sdlDisplay(world, tileX, tileY);
                if((refresh % 10) == 0)
                {
                    playerRect.x += frameSize;
                    if(playerRect.x >= textureWidth) playerRect.x = 0;
                }

                SDL_RenderCopy(renderer, im_PlayerImage.getTexture(), &playerRect, &playerPosition);

                SDL_RenderPresent(renderer);
                tileY = tileY + 2;
                refresh++;
            }
            break;

        case 'l':
            tileX = 0;
            tileY = 0;
            playerRect.y = frameSize;
            while(tileX < TAILLE_SPRITE)
            {
                sdlDisplay(world, tileX, tileY);

                if((refresh % 10) == 0)
                {
                    playerRect.x += frameSize;
                    if(playerRect.x >= textureWidth) playerRect.x = 0;
                }

                SDL_RenderCopy(renderer, im_PlayerImage.getTexture(), &playerRect, &playerPosition);

                SDL_RenderPresent(renderer);
                tileX = tileX + 2;
                refresh++;
            }
            break;

        case 'd':
            cout << "je repasse ici" << endl;
            tileX = 0;
            tileY = 0;
            playerRect.y = 0;
            while(tileY >= -TAILLE_SPRITE)
            {
                sdlDisplay(world, tileX, tileY);
        
                if((refresh % 10) == 0)
                {
                    playerRect.x += frameSize;
                    if(playerRect.x >= textureWidth) playerRect.x = 0;
                }

                SDL_RenderCopy(renderer, im_PlayerImage.getTexture(), &playerRect, &playerPosition);

                SDL_RenderPresent(renderer);
                tileY = tileY - 2;
                refresh++;
                cout << refresh << endl;
            }
            break;

        case 'r':
            tileX = 0;
            tileY = 0;
            playerRect.y = 2*frameSize;
            while(tileX >= -TAILLE_SPRITE)
            {
                sdlDisplay(world, tileX, tileY);

                if((refresh % 10) == 0)
                {
                    playerRect.x += frameSize;
                    if(playerRect.x >= textureWidth) playerRect.x = 0;
                }

                SDL_RenderCopy(renderer, im_PlayerImage.getTexture(), &playerRect, &playerPosition);

                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
                tileX = tileX - 2;
                refresh++;
            }
            break;

        default:
            break;
    }
}

void SdlGame::sdlDisplay(world world, int tileX, int tileY)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int Xplayer = world.mainPlayer.getPosX();
    int Yplayer = world.mainPlayer.getPosY();

    for(int x = Yplayer - 5; x < Yplayer + 6; x++)
    {
        for(int y = Xplayer - 5; y < Xplayer + 6; y++)
        {
            if(x >= 0 && x < SIZETERRAIN && y >= 0 && y < SIZETERRAIN)
            {
                if(world.mainTerrain.terrainTab[y][x] == '#')
                {
                    im_Tree.draw(renderer, ((x-Yplayer+4)*TAILLE_SPRITE)+tileX, ((y-Xplayer+4)*TAILLE_SPRITE)+tileY, TAILLE_SPRITE, TAILLE_SPRITE);
                }
                if(world.mainTerrain.terrainTab[y][x] == '.')
                {
                    im_GrassLand.draw(renderer, ((x-Yplayer+4)*TAILLE_SPRITE)+tileX, ((y-Xplayer+4)*TAILLE_SPRITE)+tileY, TAILLE_SPRITE, TAILLE_SPRITE);
                }
                if(world.mainTerrain.terrainTab[y][x] == 'H')
                {
                    im_herbs.draw(renderer, ((x-Yplayer+4)*TAILLE_SPRITE)+tileX, ((y-Xplayer+4)*TAILLE_SPRITE)+tileY, TAILLE_SPRITE, TAILLE_SPRITE);
                }
                if((world.mainTerrain.terrainTab[y][x] == 'O') || (world.mainTerrain.terrainTab[y][x] == 'N') || (world.mainTerrain.terrainTab[y][x] == 'V'))
                {
                    im_MissingTexture.draw(renderer, ((x-Yplayer+4)*TAILLE_SPRITE)+tileX, ((y-Xplayer+4)*TAILLE_SPRITE)+tileY, TAILLE_SPRITE, TAILLE_SPRITE);
                }
            }
        }
    }

    if(!world.hasMoved)
    {
        SDL_Rect tempPosPlayer = playerRect;

        switch (world.mainPlayer.getOrientation())
        {
            case 'n':
                tempPosPlayer.x = 0;
                tempPosPlayer.y = 3*frameSize;
                break;
            
            case 's':
                tempPosPlayer.x = 0;
                tempPosPlayer.y = 0;
                break;
            
            case 'e':
                tempPosPlayer.x = 0;
                tempPosPlayer.y = 2*frameSize;
                break;

            case 'o':
                tempPosPlayer.x = 0;
                tempPosPlayer.y = frameSize;
                break;
        
            default:
                break;
        }
        SDL_RenderCopy(renderer, im_PlayerImage.getTexture(), &tempPosPlayer, &playerPosition);
    }
}

void SdlGame::sdlLoop(world & world)
{
    SDL_Event events;
    bool quit = false;
    world.hasMoved = false;
    char moveDirection;

    while(!quit)
    {
        while(SDL_PollEvent(&events))
        {
            if(events.type == SDL_QUIT) quit = true;
            else if (events.type == SDL_KEYDOWN)
            {
                switch(events.key.keysym.sym)
                {
                    case SDLK_UP:
                        world.mainPlayer.setOrientation('n');
                        if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX()-1, world.mainPlayer.getPosY()))
                            {
                                moveDirection = 'u';
                                world.hasMoved = true;
                            }
                            break;

                    case SDLK_LEFT:
                        world.mainPlayer.setOrientation('o');
                        if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY()-1))
                            {
                                moveDirection = 'l';
                                world.hasMoved = true;
                            } 
                            break;

                    case SDLK_DOWN:
                        world.mainPlayer.setOrientation('s');
                        if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX()+1 , world.mainPlayer.getPosY()))
                            {
                                moveDirection = 'd';
                                world.hasMoved = true;
                            }
                            break;

                    case SDLK_RIGHT:
                        world.mainPlayer.setOrientation('e');
                        if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY() + 1))
                            {
                                moveDirection = 'r';
                                world.hasMoved = true;
                            }
                            break;

                    case SDLK_m: 
                        world.menuOn = !world.menuOn;
                        break;
                    
                    case SDLK_x: 
                        quit=true;
                        break; 

                    case SDLK_1:
                        if(world.menuOn)
                        {
                            world.displayPokemon();
                        }      
                        break;

                    case SDLK_2:
                        if(world.menuOn)
                        {
                            world.saveGame("saveData");
                            world.menuOn = false;
                        }
                        break;

                    case SDLK_3:
                        if(world.menuOn)
                        {
                            world.loadGame("saveData");
                            world.menuOn = false;
                        }
                        break;

                    case SDLK_4:
                        if(world.menuOn)
                        {
                            quit = true;
                        }
                        break;

                    default:
                        break;
                }
            }

        }

        if(world.menuOn)
        {
            sdlDisplayMenu();
            //sdlDisplayChatBox();
            //sdlDisplayBattle();
        }

        if(world.hasMoved)
        {
            sdlLaunchAnimation(world, moveDirection);
            switch (moveDirection)
            {
                case 'u':
                    world.mainPlayer.moveUp();
                    break;

                case 'l':
                    world.mainPlayer.moveLeft();
                    break;

                case 'd':
                    world.mainPlayer.moveDown();
                    break;

                case 'r':
                    world.mainPlayer.moveRight();
                    break;
            
                default:
                    break;
            }

            world.door();
            world.randomCombat(world.mainPlayer);
			world.healAll(world.mainPlayer);
			
			world.hasMoved = false;
        }

        if(!world.menuOn)
        {
            sdlDisplay(world, 0, 0);
        }

        SDL_RenderPresent(renderer);
    }
}

void SdlGame::sdlDisplayMenu()
{
        SDL_Rect r;
        r.x = 384;          
        r.y = 0;
        r.w = 256;
        r.h = 640;
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, &r);
        SDL_Rect positionMenu1;
        positionMenu1.x = 400;
        positionMenu1.y = 50;
        positionMenu1.w = 200;
        positionMenu1.h = 50;
        SDL_RenderCopy(renderer, font_menuPoke.getTexture(),NULL, &positionMenu1);
        positionMenu1.y += 100;
        SDL_RenderCopy(renderer,font_menuSave.getTexture(), NULL, &positionMenu1);
        positionMenu1.y += 100;
        SDL_RenderCopy(renderer,font_menuLoad.getTexture(), NULL, &positionMenu1);
        positionMenu1.y += 100;
        SDL_RenderCopy(renderer, font_menuQuit.getTexture(), NULL, &positionMenu1);
}

void SdlGame::sdlDisplayChatBox()
{
    im_chatBox.draw(renderer,0,448,639,200);
}

void SdlGame::sdlDisplayBattle()
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 440;
    rect.w = 640;
    rect.h = 200;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, im_chatBox.getTexture(),NULL, &rect);
    



}