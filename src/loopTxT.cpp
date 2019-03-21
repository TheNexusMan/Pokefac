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
	bool isOk = true;
	int key;

	do {
#ifdef _WIN32
		Sleep(100);
#else
		usleep(100000);
#endif
		termClear();
		world.mainTerrain.displayTerrain(world.mainPlayer);
		key = win.getCh();
		{
			switch (key)
			{
			case 'i':
			if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX() -1, world.mainPlayer.getPosY()))
			{
				world.mainPlayer.moveUp();
			}
				break;
			case 'j':
			if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY()-1))
			{
				world.mainPlayer.moveLeft();
			}
				break;
			case 'k':
			if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX()+1, world.mainPlayer.getPosY()))
			{
				world.mainPlayer.moveDown();
			}
				break;
			case 'l':
			if(world.moveIsAllowed(world.mainPlayer, world.mainPlayer.getPosX(), world.mainPlayer.getPosY()+1))
			{
				world.mainPlayer.moveRight();
			}
				break;
			case 'q':
				isOk = false;
				break;

			}

		}
	} while (isOk);
	
}