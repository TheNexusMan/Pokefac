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

void Image::loadFromFile(const char *filename, SDL_Renderer *renderer)
{
    surface = IMG_Load(filename);
    if (surface == NULL)
    {
        string nfn = string("../") + filename;
        cout << "Error : Impossible de lire " << filename << ". Tentative de lecture de : " << nfn << endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL)
        {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL)
    {
        cout << "Error : Impossible de lire " << filename << endl;
        exit(1);
    }
    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        cout << "Error : Probleme lors de la création de la texture provenant de : " << filename << endl;
        exit(1);
    }
}

void Image::loadFromCurrentSurface(SDL_Renderer *renderer)
{
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        cout << "Error : Probleme lors de la création de la texture provenant de la surface" << endl;
        exit(1);
    }
}

void Image::draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? surface->w : w;
    r.h = (h < 0) ? surface->h : h;

    if (has_changed)
    {
        ok = SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }
    ok = SDL_RenderCopy(renderer, texture, NULL, &r);
    assert(ok == 0);
}

SDL_Texture *Image::getTexture() const
{
    return texture;
}
void Image::setSurface(SDL_Surface *surf)
{
    surface = surf;
}

// ======================================= CLASS SDLJEU ===================================  //

SdlGame::SdlGame()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initalisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image impossible a initialisé, SDL_image error : " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer impossible a initialisé, SDL_mixer error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        withSound = false;
    }
    else
        withSound = true;

    int dimx, dimy;
    //dimx = SIZETERRAIN * TAILLE_SPRITE;
    //dimy = SIZETERRAIN * TAILLE_SPRITE;
    dimx = 9 * TAILLE_SPRITE;
    dimy = 9 * TAILLE_SPRITE;

    //Creation de la fenetre
    window = SDL_CreateWindow("PokeFac", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "Erreur lors de la création de la fenetre ! Erreur SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Ajout ici du chargement des images
    im_Tree.loadFromFile("./data/textures/tree.png", renderer);
    im_GrassLand.loadFromFile("./data/textures/grass03.png", renderer);
    im_herbs.loadFromFile("./data/textures/haute_herbes.png", renderer);
    im_MissingTexture.loadFromFile("./data/textures/error.png", renderer);
    im_chatBox.loadFromFile("./data/textures/chatbox.png", renderer);
    im_battleBG.loadFromFile("./data/textures/battleBG.png", renderer);
    im_sandRoad.loadFromFile("./data/textures/sand_road.jpg",renderer);
    im_arena.loadFromFile("./data/textures/arena.png", renderer);
    im_PlayerImage.loadFromFile("./data/textures/playerSprite.png", renderer);
    im_House.loadFromFile("./data/textures/house.png", renderer);
    im_Wood.loadFromFile("./data/textures/wood.jpg", renderer);
    im_Arrow.loadFromFile("./data/textures/sprite_arrow.png", renderer);
    im_Life.loadFromFile("./data/textures/life.png", renderer);
    //fin de l'ajout du chargement des images

    //Pokemons
    im_linuchu.loadFromFile("./data/textures/linuchu.png", renderer);

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

    font = TTF_OpenFont("./data/font/pokemon_pixel_font.ttf", 50);
    if (font == NULL)
    {
        cout << "Failed to load the font SDL_TTF : " << TTF_GetError() << endl;
    }
    font_color.r = 0;
    font_color.g = 0;
    font_color.b = 0;

    font_red.r = 255;
    font_red.g = 0;
    font_red.b = 0;

    font_green.r = 0;
    font_green.g = 255;
    font_green.b = 0;

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

    font_gameSaved.setSurface(TTF_RenderText_Solid(font, "Partie Sauvegardee", font_color));
    font_gameSaved.loadFromCurrentSurface(renderer);

    font_gameLoaded.setSurface(TTF_RenderText_Solid(font, "Partie Chargee", font_color));
    font_gameLoaded.loadFromCurrentSurface(renderer);

    font_choosePoke.setSurface(TTF_RenderText_Solid(font, "Organiser vos pokemons", font_color));
    font_choosePoke.loadFromCurrentSurface(renderer);
    


    // Sounds
    if (withSound)
    {

        //chargement des musiques 
        sound = Mix_LoadMUS("./data/music/generalSong.wav");
        battle = Mix_LoadMUS("./data/music/battleMusic.wav");
        if ((sound == NULL) || (battle == NULL))
        {
            cout << "Failed to load son.wave ! SDL_mixer Error : " << Mix_GetError() << endl;
        }
        
        //chargement des effets sonore
        footstep = Mix_LoadWAV( "./data/music/pasHerbe.wav" );

        if(footstep == NULL)
        {
            cout << "Failed to load son.wave ! SDL_mixer Error : " << Mix_GetError() << endl;
        }
    }
}

SdlGame::~SdlGame()
{
    if (withSound)
        Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SdlGame::sdlLaunchAnimation(world world, char direction)
{
    int tileX, tileY;
    unsigned int refresh = 0;
    playerRect.x = 0;
    Mix_PlayChannel(-1, footstep, 0);
    
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
                //SDL_Delay(9);
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
                //SDL_Delay(9);
            }
            break;

        case 'd':
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
                //SDL_Delay(9);
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
                //SDL_Delay(9);
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

    string terrainName = world.mainTerrain.terrainName;
    terrainName.pop_back();

    int Xplayer = world.mainPlayer.getPosX();
    int Yplayer = world.mainPlayer.getPosY();

    for (int x = Yplayer - SIZETERRAIN; x < Yplayer + SIZETERRAIN; x++)
    {
        for (int y = Xplayer - SIZETERRAIN; y < Xplayer + SIZETERRAIN; y++)
        {

            if (x >= 0 && x < SIZETERRAIN && y >= 0 && y < SIZETERRAIN)
            {
                if(x == 0 && y == 0 && terrainName == "terrain")
                {
                    im_GrassLand.draw(renderer, ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY, TAILLE_SPRITE*SIZETERRAIN, TAILLE_SPRITE*SIZETERRAIN);
                }

                if(x == 4 && y == 4 && terrainName == "house")
                {
                    im_Wood.draw(renderer, ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY, TAILLE_SPRITE*(SIZETERRAIN-8), TAILLE_SPRITE*(SIZETERRAIN-8));
                }

                if(world.mainTerrain.terrainTab[y][x] == '#')
                {
                    im_Tree.draw(renderer, ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY-30, TAILLE_SPRITE+20, TAILLE_SPRITE+30);
                }

                if(world.mainTerrain.terrainTab[y][x] == 'H')
                {
                    im_herbs.draw(renderer, ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY, TAILLE_SPRITE, TAILLE_SPRITE);
                }

                if(world.mainTerrain.terrainTab[y][x] == 'R')
                {
                    im_sandRoad.draw(renderer, ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY, TAILLE_SPRITE, TAILLE_SPRITE);
                }
                
                if(world.mainTerrain.terrainTab[y][x] == 'M')
                {
                    im_House.draw(renderer,((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY, TAILLE_SPRITE*5, TAILLE_SPRITE*5);
                }

                if(world.mainTerrain.terrainTab[y][x] == 'O')
                {
                    Door thisDoor = world.whichDoor(y, x);
                    SDL_Rect arrowRect;
                    arrowRect.w = arrowRect.h = 50;
                    arrowRect.y = 0;
                    switch (thisDoor.orientation)
                    {
                    case 'n':
                        arrowRect.x = 50;
                        break;
                    
                    case 's':
                        arrowRect.x = 150;
                        break;
                    
                    case 'e':
                        arrowRect.x = 0;
                        break;
                    
                    case 'o':
                        arrowRect.x = 100;
                        break;
                    
                    default:
                        break;
                    }
                    
                    SDL_Rect doorPosition;
                    doorPosition.x = ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX;
                    doorPosition.y = ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY;
                    doorPosition.w = doorPosition.h = TAILLE_SPRITE;
                    SDL_RenderCopy(renderer, im_Arrow.getTexture(), &arrowRect, &doorPosition);
                }

                if((world.mainTerrain.terrainTab[y][x] == 'V'))
                {
                    im_Life.draw(renderer, ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY, TAILLE_SPRITE, TAILLE_SPRITE);
                }

                if((world.mainTerrain.terrainTab[y][x] == 'N'))
                {
                    im_MissingTexture.draw(renderer, ((x - Yplayer + 4) * TAILLE_SPRITE) + tileX, ((y - Xplayer + 4) * TAILLE_SPRITE) + tileY, TAILLE_SPRITE, TAILLE_SPRITE);
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




///////////////////////////////////
//              LOOP             //
///////////////////////////////////

void SdlGame::sdlLoop(world &world)
{
    SDL_Event events;
    bool quit = false;
    world.hasMoved = false;
    char moveDirection;

    Uint32 deltaTime = SDL_GetTicks(), elapsedTime;
    Mix_PlayMusic( sound, -1 );

    while(!quit)
    {
        // termClear();
        // world.mainTerrain.displayTerrain(world.mainPlayer);

        SDL_FlushEvent(events.type);
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true;
            else if (events.type == SDL_KEYDOWN)
            {
                switch (events.key.keysym.sym)
                {
                    case SDLK_UP:
                        world.mainPlayer.setOrientation('n');
                        if((world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX()-1, world.mainPlayer.getPosY())) && world.menuOn == 0 && !world.isInBattle)
                            {
                                moveDirection = 'u';
                                world.hasMoved = true;
                            }
                            break;

                    case SDLK_LEFT:
                        world.mainPlayer.setOrientation('o');
                        if((world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY()-1)) && world.menuOn == 0 && !world.isInBattle)
                            {
                                moveDirection = 'l';
                                world.hasMoved = true;
                            } 
                            break;

                    case SDLK_DOWN:
                        world.mainPlayer.setOrientation('s');
                        if((world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX()+1 , world.mainPlayer.getPosY())) && world.menuOn == 0 && !world.isInBattle)
                            {
                                moveDirection = 'd';
                                world.hasMoved = true;
                            }
                            break;

                    case SDLK_RIGHT:
                        world.mainPlayer.setOrientation('e');
                        if((world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY() + 1)) && world.menuOn == 0 && !world.isInBattle)
                            {
                                moveDirection = 'r';
                                world.hasMoved = true;
                            }
                            break;

                    case SDLK_m:
                        if(world.menuOn == 1)
                        {
                            world.menuOn = 0;
                        }else if(world.menuOn == 0)
                        {
                            world.menuOn = 1;
                        }else if (world.menuOn == 2)
                        {
                            world.menuOn = 0;
                        }else if (world.menuOn == 3)
                        {
                            sdlDisplayPokemonMenu(world, false);
                            world.menuOn = 2;
                        }
                            
                        break;
                    
                    case SDLK_x: 
                        quit=true;
                        break; 

                    case SDLK_1:
                        if(world.menuOn == 1)
                        {
                            //world.displayPokemon();
                            sdlDisplayPokemonMenu(world, false);
                        }else if(world.menuOn == 2)
                        {
                            if(world.mainPlayer.nbPokemon > 0)
                                sdlDisplayPokemonInfos(world, 0);
                        }
                        if(world.isInBattle)
                        {
                            sdlDisplayBattle(world, 1);
                        }
                        break;

                    case SDLK_2:
                        if(world.menuOn == 1)
                        {
                            world.saveGame("saveData");
                            world.menuOn = 0;
                        }else if(world.menuOn == 2)
                        {
                            if(world.mainPlayer.nbPokemon > 1)
                                sdlDisplayPokemonInfos(world, 1);
                        }
                        if(world.isInBattle)
                        {
                            sdlDisplayBattle(world, 2);
                        }
                        break;

                    case SDLK_3:
                        if(world.menuOn == 1)
                        {
                            world.loadGame("saveData");
                            world.menuOn = 0;
                        }else if(world.menuOn == 2)
                        {
                            if(world.mainPlayer.nbPokemon > 2)
                                sdlDisplayPokemonInfos(world, 2);
                        }
                        if(world.isInBattle)
                        {
                            sdlDisplayBattle(world, 3);
                        }
                        break;

                    case SDLK_4:
                        if(world.menuOn == 1)
                        {
                            quit = true;
                        }else if(world.menuOn == 2)
                        {
                            if(world.mainPlayer.nbPokemon > 3)
                                sdlDisplayPokemonInfos(world, 3);
                        }
                        if(world.isInBattle)
                        {
                            sdlDisplayBattle(world, 4);
                        }
                        break;
                    
                    case SDLK_5:
                        if(world.menuOn == 2)
                        {
                            if(world.mainPlayer.nbPokemon > 4)
                                sdlDisplayPokemonInfos(world, 4);
                        }
                        if(world.isInBattle)
                        {
                            sdlDisplayBattle(world, 5);
                        }
                        break;
                    
                    case SDLK_6:
                        if(world.menuOn == 2)
                        {
                            if(world.mainPlayer.nbPokemon > 5)
                                sdlDisplayPokemonInfos(world, 5);
                        }
                        break;

                    default:
                        break;
                }
            }
        }

        if (world.menuOn == 1)
        {
            sdlDisplayMenu();
            //sdlDisplayChatBox(world);
            // sdlDisplayBattle(deltaTime, elapsedTime, false);
            //sdlDisplayPokemonMenu(world, true);
        }

        if(world.isSaving)
        {
            sdlDisplayGameSaved(deltaTime, elapsedTime, world);

        }
        if(world.isLoading)
        {
            sdlDisplayGameLoaded(deltaTime, elapsedTime, world);
        }

        if(world.isInBattle)
        {
            sdlDisplayBattle(world, 0);
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
            

            sdlRandomCombat(world);
			world.healAll(world.mainPlayer);
			world.hasMoved = false;
            sdlNPCBattle(world);
        }

        if (world.menuOn == 0 && !world.isSaving && !world.isLoading && !world.isInBattle)
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_Rect positionMenu1;
    positionMenu1.x = 400;
    positionMenu1.y = 50;
    positionMenu1.w = 200;
    positionMenu1.h = 50;
    SDL_RenderCopy(renderer, font_menuPoke.getTexture(), NULL, &positionMenu1);
    positionMenu1.y += 100;
    SDL_RenderCopy(renderer, font_menuSave.getTexture(), NULL, &positionMenu1);
    positionMenu1.y += 100;
    SDL_RenderCopy(renderer, font_menuLoad.getTexture(), NULL, &positionMenu1);
    positionMenu1.y += 100;
    SDL_RenderCopy(renderer, font_menuQuit.getTexture(), NULL, &positionMenu1);
}

void SdlGame::sdlDisplayChatBox(world world)
{
    im_chatBox.draw(renderer, 0, 448, 639, 200);
 SDL_Rect textPos;
    textPos.x = 25;
    textPos.y = 468;
    textPos.w = 590;
    textPos.h = 150;

    string sentence = world.NPCTab[0].dialog[0];
    font_chatBox.setSurface(TTF_RenderText_Solid(font, sentence.c_str(), font_color));
    font_chatBox.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_chatBox.getTexture(), NULL, &textPos);
}


void SdlGame::sdlDisplayGameSaved(Uint32 &deltaTime, Uint32 &elapsedTime, world &world)
{
    elapsedTime = SDL_GetTicks();
    Uint32 timing = elapsedTime - deltaTime;

    SDL_Rect rectOne;
    rectOne.x = 35;
    rectOne.y = 468;
    rectOne.w = 550;
    rectOne.h = 125;

    SDL_Rect rectTwo;
    rectTwo.x = 75;
    rectTwo.y = 490;
    rectTwo.w = 450;
    rectTwo.h = 75;

  /*   cout << "elaps = " << elapsedTime << endl;
    cout << "delta = " << deltaTime << endl; 
    cout << timing << endl; */

    bool display = true;
    if(timing > 2500)
    {
        display = false;
	    world.isSaving = false;

        deltaTime = elapsedTime;

    }
    if(display)
    {
        SDL_RenderCopy(renderer, im_chatBox.getTexture(), NULL, &rectOne);
        SDL_RenderCopy(renderer, font_gameSaved.getTexture(), NULL, &rectTwo);

    }
}

void SdlGame::sdlDisplayGameLoaded(Uint32 &deltaTime, Uint32 &elapsedTime, world &world)
{
    elapsedTime = SDL_GetTicks();
    Uint32 timing = elapsedTime - deltaTime;

    SDL_Rect rectOne;
    rectOne.x = 35;
    rectOne.y = 468;
    rectOne.w = 550;
    rectOne.h = 125;

    SDL_Rect rectTwo;
    rectTwo.x = 75;
    rectTwo.y = 490;
    rectTwo.w = 450;
    rectTwo.h = 75;


    bool display = true;
    if(timing > 3000)
    {
        display = false;
	    world.isLoading = false;

        deltaTime = elapsedTime;

    }
    if(display)
    {
        SDL_RenderCopy(renderer, im_chatBox.getTexture(), NULL, &rectOne);
        SDL_RenderCopy(renderer, font_gameLoaded.getTexture(), NULL, &rectTwo);
        //im_chatBox.draw(renderer,35,468,550,125);
    }
}

void SdlGame::sdlDisplayPokemonMenu(world &world, bool inBattle)
{
    world.menuOn = 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Rect forBattle;
    forBattle.x = 50;
    forBattle.y = 35;
    forBattle.h = 35;
    forBattle.w = 200;

    SDL_Rect hpPos;
    hpPos.x = 50;
    hpPos.y = forBattle.y + 40;
    hpPos.h = 35;
    hpPos.w = 100;

    string pokemonNameStr;
    string pokemonHP;
    //Boite de dialogue bas (Cas changement de pokemon)
    if(inBattle)
    {

        im_chatBox.draw(renderer,0,480,640,160);
        font_choosePoke.draw(renderer,35,500,550,115);
        for(int i = 0; i < 6; i++)
        {
            pokemonNameStr = world.pokeTab[i].name;
            pokemonHP = "-- HP : " + to_string(world.pokeTab[i].health) + " / " + to_string(world.pokeTab[i].maxHealth);

            font_pokemonName.setSurface(TTF_RenderText_Solid(font, pokemonNameStr.c_str(), font_color));
            font_pokemonName.loadFromCurrentSurface(renderer);

            font_pokemonHP.setSurface(TTF_RenderText_Solid(font, pokemonHP.c_str(), font_color));
            font_pokemonHP.loadFromCurrentSurface(renderer);

            SDL_RenderCopy(renderer, font_pokemonName.getTexture(), NULL, &forBattle);
            SDL_RenderCopy(renderer, font_pokemonHP.getTexture(), NULL, &hpPos);
            forBattle.y +=75;
            hpPos.y = forBattle.y + 30;
        }
    } else
    {
        forBattle.y += 5;
        hpPos.y +=5;
        for(unsigned int i = 0; i < world.mainPlayer.nbPokemon; i++)
        {
            pokemonNameStr = world.mainPlayer.tabPokemon[i].name;
            pokemonHP = "-- HP : " + to_string(world.mainPlayer.tabPokemon[i].health) + " / " + to_string(world.mainPlayer.tabPokemon[i].maxHealth);

            font_pokemonName.setSurface(TTF_RenderText_Solid(font, pokemonNameStr.c_str(), font_color));
            font_pokemonName.loadFromCurrentSurface(renderer);

            font_pokemonHP.setSurface(TTF_RenderText_Solid(font, pokemonHP.c_str(), font_color));
            font_pokemonHP.loadFromCurrentSurface(renderer);

            SDL_RenderCopy(renderer, font_pokemonName.getTexture(), NULL, &forBattle);
            SDL_RenderCopy(renderer, font_pokemonHP.getTexture(), NULL, &hpPos);
            forBattle.y +=100;
            hpPos.y = forBattle.y + 30;
        }
    }
}

void SdlGame::sdlDisplayPokemonInfos(world &world, int idPoke)
{
    world.menuOn = 3;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);

    SDL_Rect posT;
    posT.x = 50;
    posT.y = 35;
    posT.h = 40;
    posT.w = 200;


    string pokemonName, pokemonTypeInfo, pokemonType, pokemonAttacks, pokemonDamages;


    pokemonName = world.pokeTab[idPoke].name;
    pokemonTypeInfo = "Type :";
    pokemonType = world.pokeTab[idPoke].type;
    font_pokemonName.setSurface(TTF_RenderText_Solid(font, pokemonName.c_str(), font_color));
    font_pokemonName.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_pokemonName.getTexture(), NULL, &posT);

    posT.x = 350;
    posT.w = 50;

    font_pokemonType.setSurface(TTF_RenderText_Solid(font, pokemonTypeInfo.c_str(), font_color));
    font_pokemonType.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_pokemonType.getTexture(),NULL, &posT);

    posT.x +=75;

    font_pokemonType.setSurface(TTF_RenderText_Solid(font, pokemonType.c_str(), font_color));
    font_pokemonType.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_pokemonType.getTexture(),NULL, &posT);

    posT.x = 50;
    posT.y = 150;
    posT.w = 200;

    pokemonAttacks = "Attaques :";
    font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, pokemonAttacks.c_str(), font_color));
    font_pokemonAttacks.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(),NULL, &posT);
    posT.x = 350;
    pokemonAttacks = "Degats :";
    font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, pokemonAttacks.c_str(), font_color));
    font_pokemonAttacks.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(),NULL, &posT);

    posT.x = 50;
    posT.y = 225;

    SDL_Rect posD;
    posD.x = 350;
    posD.y = 225;
    posD.h = 40;
    posD.w = 50;

    for(int i = 0; i < 4; i++)
    {
        pokemonAttacks = world.pokeTab[idPoke].attackChoice[i].name;
        font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, pokemonAttacks.c_str(), font_color));
        font_pokemonAttacks.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(),NULL, &posT);
        posT.y += 100;
        pokemonAttacks = to_string(world.pokeTab[idPoke].attackChoice[i].damagePoints);
        font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, pokemonAttacks.c_str(), font_color));
        font_pokemonAttacks.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(),NULL, &posD);
        posD.y += 100;
    }
}

void SdlGame::sdlDisplayBattleOpponentLife(world world)
{
    // Affichage boite de vie et de nom du pokemon sauvage/dresseur

    string pokemonHealth = "HP : " + to_string(world.pokeInFight.health) + "/" + to_string(world.pokeInFight.maxHealth);

    SDL_Rect posLife;
    posLife.x = 60;
    posLife.y = 150;
    posLife.w = 180;
    posLife.h = 60;
    
    im_chatBox.draw(renderer, 50,50,250,200);
    if(world.pokeInFight.health < 15)
    {
        font_pokemonHP.setSurface(TTF_RenderText_Solid(font, pokemonHealth.c_str(), font_red));
        font_pokemonHP.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonHP.getTexture(), NULL, &posLife); 
    } else
    {
        font_pokemonHP.setSurface(TTF_RenderText_Solid(font, pokemonHealth.c_str(), font_green)); 
        font_pokemonHP.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonHP.getTexture(), NULL, &posLife);   
    }
    
    posLife.y = 80;
    font_pokemonHP.setSurface(TTF_RenderText_Solid(font, world.pokeInFight.name.c_str(), font_color));
    font_pokemonHP.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_pokemonHP.getTexture(), NULL, &posLife); //affichage nom
}

void SdlGame::sdlDisplayBattlePlayerLife(Pokemon playerPoke)
{
    // Boite de vie et du nom du pokémon du joueur
    string yourLife = "HP : " + to_string(playerPoke.health) + "/" + to_string(playerPoke.maxHealth);
    im_chatBox.draw(renderer, 375, 300, 200,125);

    SDL_Rect posLife;
    posLife.x = 400;
    posLife.y = 330;
    posLife.w = 115;
    posLife.h = 60;

    if(playerPoke.health < 15)
    {
        font_pokemonHP.setSurface(TTF_RenderText_Solid(font, yourLife.c_str(), font_red));
        font_pokemonHP.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonHP.getTexture(), NULL, &posLife); //affichage vie
    } else
    {
        font_pokemonHP.setSurface(TTF_RenderText_Solid(font, yourLife.c_str(), font_green));
        font_pokemonHP.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonHP.getTexture(), NULL, &posLife); //affichage vie
    }
}

void SdlGame::sdlDisplayBattleSentence(string sentence, string sentence2)
{
    im_chatBox.draw(renderer,0,440,640,200);

    SDL_Rect posSentence;
    posSentence.x = 30;
    posSentence.y = 470;
    posSentence.w = sentence.size()*12;
    posSentence.h = 50;

    font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, sentence.c_str(), font_color));
    font_pokemonAttacks.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(), NULL, &posSentence);

    if(sentence2 != "")
    {
        posSentence.y = 520;
        posSentence.w = sentence2.size()*12;
        font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, sentence2.c_str(), font_color));
        font_pokemonAttacks.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(), NULL, &posSentence);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(2500);
}

void SdlGame::sdlDisplayBattle(world & world, unsigned int action)
{
    srand(time(NULL));
    bool hasAttacked = false;
    Pokemon * playerPoke = &world.mainPlayer.firstPokemonAlive();

    // Si une attaque a été lancé par le joueur
    if(action > 0 && action < 5)
    {
        world.pokeInFight.receiveAttack(playerPoke->attackChoice[action-1]);
        hasAttacked = true;

        string sentence = "Vous attaquez avec " + playerPoke->attackChoice[action-1].name + " " + to_string(playerPoke->attackChoice[action-1].damagePoints);
        sdlDisplayBattleSentence(sentence);
    }

    im_battleBG.draw(renderer, 0, 0, 640, 440);
    sdlDisplayBattleOpponentLife(world);
    sdlDisplayBattlePlayerLife(*playerPoke);
    

    im_linuchu.draw(renderer, 375, 100, 150,150); // affichage du pokemon adverse (les coordonnées)
    im_linuchu.draw(renderer, 175, 350, 150,150); // affichage du pokemon joueur


    // Si le pokémon est vaincu et qu'on peut l'attraper
    if(!world.isAgainstNPC && world.pokeInFight.health == 0)
    {
        string sentence = "Victoire !";
        string sentence2;
        if(world.mainPlayer.getPokeball() > 0 && world.mainPlayer.hasFreePokeLocation() && !world.mainPlayer.hasThisPokemon(world.pokeInFight))
        {
            world.mainPlayer.addPokemon(world.pokeInFight);
            world.mainPlayer.usePokeball();
            world.isInBattle = false;
            sentence2 = "Le pokemon est attrape !";
        }
        else if(world.mainPlayer.hasThisPokemon(world.pokeInFight))
        {
            world.isInBattle = false;
            sentence2 = "Vous possedez deja ce pokemon";
        }
		else if(!world.mainPlayer.hasFreePokeLocation() && !world.mainPlayer.hasThisPokemon(world.pokeInFight))
        {
            world.isInBattle = false;
            sentence2 = "Plus de place pour ce pokemon";
        }
            
		else{
            world.isInBattle = false;
            sentence2 = "Vous n'avez plus de pokeball";
        }
        
        sdlDisplayBattleSentence(sentence, sentence2);
    }

    // Si le dresseur adverse est vaincu
    if(world.isAgainstNPC && world.pokeInFight.health == 0)
    {
        world.mainPlayer.addMoney(100);
        world.isInBattle = false;
        world.NPCInFight->beaten = true;
        string sentence = world.NPCInFight->name + " est vaincu !";
        string sentence2 = "Vous recevez 100 pokedollars";
        sdlDisplayBattleSentence(sentence, sentence2);
    }

    // Le pokémon adverse nous attaque après notre attaque
    if(hasAttacked && world.isInBattle)
    {
        int opponentAttack = rand() % 3;
        playerPoke->receiveAttack(world.pokeInFight.attackChoice[opponentAttack]);
        string sentence;
        if(world.isAgainstNPC)
            sentence = world.NPCInFight->name + " attaque avec " + world.pokeInFight.attackChoice[opponentAttack].name + " " + to_string(world.pokeInFight.attackChoice[opponentAttack].damagePoints);
        else
            sentence = world.pokeInFight.name + " attaque avec " + world.pokeInFight.attackChoice[opponentAttack].name + " " + to_string(world.pokeInFight.attackChoice[opponentAttack].damagePoints);
        sdlDisplayBattleSentence(sentence);
    }

    // Si le pokémon du joueur est mort
    if(playerPoke->health == 0 && world.isInBattle)
    {
        string sentence;
        sdlDisplayBattlePlayerLife(*playerPoke);

        if(world.mainPlayer.allPokemonsAreDead())
        {
            world.mainPlayer.treatAllPokemon();
            world.teleport(world.mainPlayer, "house1", 9, 10);
            world.isInBattle = false;

            sentence = "Defaite...";
        }else{

            sentence = playerPoke->name + " est KO, " + world.mainPlayer.firstPokemonAlive().name + " est envoye !";
        }
        
        sdlDisplayBattleSentence(sentence);
    }
    
    // Affichage des différentes attaques possibles
    if(action != 5 && world.isInBattle)
    {
        im_chatBox.draw(renderer,0,440,640,200);
        string attacksName;
        SDL_Rect posAttacks;
        posAttacks.x = 40;
        posAttacks.y = 460;
        posAttacks.w = 100;
        posAttacks.h = 80;

        for(int i = 0; i < 4; i++)
        {
            attacksName = to_string(i+1) + "-" + playerPoke->attackChoice[i].name + " " + to_string(playerPoke->attackChoice[i].damagePoints);

            font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, attacksName.c_str(), font_color));
            font_pokemonAttacks.loadFromCurrentSurface(renderer);
            SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(), NULL, &posAttacks);
            
            posAttacks.x += 150;
        }

        posAttacks.x = 260;
        posAttacks.y = 540;
        attacksName = "5- Fuite";
        font_pokemonAttacks.setSurface(TTF_RenderText_Solid(font, attacksName.c_str(), font_color));
        font_pokemonAttacks.loadFromCurrentSurface(renderer);
        SDL_RenderCopy(renderer, font_pokemonAttacks.getTexture(), NULL, &posAttacks);
    }

    // Fuite
    if(action == 5 && world.isInBattle)
    {
        world.isInBattle = false;

        string sentence = "Vous prenez la fuite !";
        sdlDisplayBattleSentence(sentence);
    }

    if(world.isInBattle == false)
    {
        Mix_HaltMusic();
        Mix_PlayMusic(sound, -1);
    }
}

void SdlGame::sdlRandomCombat(world & world)
{

    if((world.isInHerb(world.mainPlayer.getPosX(), world.mainPlayer.getPosY())))
    {
        unsigned int random = world.randomNumber();

        if(random % 5 == 0)
        {
            unsigned int randomPoke = rand() % NBPOKEMON;
            world.pokeInFight = world.pokeTab[randomPoke];
            world.isInBattle = true;
            Mix_HaltMusic();
            Mix_PlayMusic(battle, -1);
        }
    }
}

void SdlGame::sdlNPCBattle(world & world)
{
	if (world.mainTerrain.terrainTab[world.mainPlayer.getPosX()][world.mainPlayer.getPosY()] == '-')
	{
		NPC * npc = world.whichNPC(world.mainPlayer);
		if (npc->beaten == 0) 
		{

            world.NPCInFight = npc;
            world.pokeInFight = npc->NPCPokemon;
            world.isInBattle = true;
            world.isAgainstNPC = true;
            string sentence = npc->name + " :";
            string sentence2 = npc->dialog[0];
            sdlDisplay(world, 0, 0);
            sdlDisplayBattleSentence(sentence, sentence2);
		}
	} 
}