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
	WinTXT win(sizeTerrain, sizeTerrain); //Get SizeTerrain (A modifier)
	bool isOk = true;
	int key;

	do {
#ifdef _WIN32
		Sleep(100);
#else
		usleep(100000);
#endif
		key = win.getCh();
		{
			switch (key)
			{
			case 'i':
				world.mainPlayer.moveUp();
				break;
			case 'j':
				world.mainPlayer.moveLeft();
				break;
			case 'k':
				world.mainPlayer.moveDown();
				break;
			case 'l':
				world.mainPlayer.moveRight();
				break;
			case 'q':
				isOk = false;
				break;

			}

		}
	} while (isOk);
	
}