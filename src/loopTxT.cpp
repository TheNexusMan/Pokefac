#include <iostream>


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "winTxt.h"
#include "world.h"

void txtLoop(world & world)
{
	WinTXT win(SIZETERRAIN, SIZETERRAIN); //Get SizeTerrain (A modifier)
	bool gameOn = true;
	bool hasMoved = false;
	int key;

	do {
#ifdef _WIN32
		Sleep(100);
#else
		usleep(100000);
#endif
		termClear();

		if(world.menuOn)
		{
			world.menu(gameOn);

			termClear();
		}

		world.mainTerrain.displayTerrain(world.mainPlayer);

		if(hasMoved)
		{
			world.randomCombat(world.mainPlayer);
			hasMoved = false;
		}

		key = win.getCh();

		{
			switch (key)
			{
				case 'z':
					if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX() -1, world.mainPlayer.getPosY()))
					{
						world.mainPlayer.moveUp();
						hasMoved = true;
					}
					break;

				case 'q':
					if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY()-1))
					{
						world.mainPlayer.moveLeft();
						hasMoved = true;
					}
					break;

				case 's':
					if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX()+1, world.mainPlayer.getPosY()))
					{
						world.mainPlayer.moveDown();
						hasMoved = true;
					}
					break;

				case 'd':
					if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY()+1))
					{
						world.mainPlayer.moveRight();
						hasMoved = true;
					}
					break;
				
				case 'm':
					world.menuOn = true;
					break;

				case 'o':
					gameOn = false;
					break;
			}

			world.door();
		}
	} while (gameOn);
}