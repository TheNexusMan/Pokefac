#include "world.h"


world::world()
{
	initPokeTab(); //Initialisation du tableau Pokémon
	initNPCTab(); // Initialisation du tableau NPC
	initPlayer(mainPlayer); // Initialise le Joueur de départ
}

void world::initPlayer(player mainPlayer)
{

	mainPlayer.initPlayer();

	if (DEBUG)
	{
		displayStars();
		cout << "Position du joueur de départ : (" << mainPlayer.getPosX() << "," << mainPlayer.getPosY() << ")" << endl;
		cout << "Argent de départ : " << mainPlayer.getMoney() << endl;
		cout << "Nombre de pokeballs : " << mainPlayer.getPokeball() << endl;
		displayStars();
	}



}

void world::initPokeTab()
{
	ifstream file("./data/pokemons.txt");

	if (file.is_open())
	{
		while (!file.eof())
		{
			for (unsigned int i = 0; i < NBPOKEMON; i++)
			{
				file >> poke[i].id;
				file >> poke[i].name;
				file >> poke[i].type;
				file >> poke[i].isFound;
				file >> poke[i].level;
				file >> poke[i].health;
				file >> poke[i].maxHealth;
				file >> poke[i].attackStat;
				file >> poke[i].defenseStat;

				for (unsigned int j = 0; j < 4; j++)
				{
					file >> poke[i].attackChoice[j].name;
					file >> poke[i].attackChoice[j].damagePoints;
				}
			}
		}

		file.close();
	}
	else {
		cout << "Erreur d'ouverture du fichier pokemons" << endl;
	}
}

void world::initNPCTab()
{
	//A remplir en fonction d'un fichier TXT (se baser sur le code au dessus)
	ifstream file("./data/NPC.txt");
	ifstream dialog("./data/NPCDialog.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			for (unsigned int i = 0; i < NB_NPC; i++)
			{
				file >> NPCTab[i].id;
				file >> NPCTab[i].name;
				file >> NPCTab[i].posX;
				file >> NPCTab[i].posY;
				file >> NPCTab[i].rotation;
			}
		}
		file.close();
	}
	else {
		cout << "Erreur dans l'ouverture du fichier ./data/NPC.txt" << endl;
	}

	//Remplie via un fichier secondaire les dialogues des NPC
	if (dialog.is_open())
	{
		while (!file.eof())
		{
			for (unsigned int i = 0; i < NB_NPC; i++)
			{
				for (unsigned j = 0; j < NB_DIALOG; j++)
				{
					dialog >> NPCTab[i].dialog[j];
				}
			}
		}
		file.close();
	}
	else
	{
		cout << "Erreur dans l'ouverture du fichier ./data/NPCDialog.txt" << endl;
		
	}


}



void world::displayStars() const
{
	for (int i = 0; i < 50; i++)
	{
		cout << "*";
	}
	cout << endl;
}

void world::debugWarning() const
{
	displayStars();
	cout << "Le programme a ete lance en mode DEBUG" << endl;
	cout << "Des informations suplementaires seront affichees dans la console" << endl << endl;
	displayStars();
	cout << endl << endl;
}


void world::initGame(NPC npc)
{
	//Placer toutes les inits ici
	

}


int world::randomNumber()
{
	int random;
	return random = rand() % 100;
	if (DEBUG)
	{
		cout << "Nombre aleatoire genere par randomNumber() => " << random << endl;
	}
}

void world::randomCombat(player mainPlayer)
{
	int random = randomNumber();
	if ((isInHerb(mainPlayer, mainPlayer.getPosX(), mainPlayer.getPosY()) && (random % 5 == 0)))
	{
		if (DEBUG)
		{
			displayStars();
			cout << "Le joueur est dans l'herbe et la condition s'avere juste" << endl;
			cout << "randomNumber() = " << random << " Random % 5 == 0" << endl;
			cout << "Lancement du combat" << endl;
			displayStars();

		}
		//Lance le combat
	} //Sinon rien
}


bool world::isInHerb(player mainPlayer, const int x, const int y) const
{
	return(mainTerrain.terrainTab[x][y] == 'H');
}


bool world::moveIsAllowed(player mainPlayer, const int x, const int y) const
{
	return ((x >= 0) && (x < SIZETERRAIN) && (y >= 0) && (y < SIZETERRAIN) && (mainTerrain.terrainTab[x][y] != '#') && (mainTerrain.terrainTab[x][y] != 'N'));
}

void world::isInLine(NPC npc, player mainPlayer, const int x, const int y) const
{
	int npcPosX = npc.getPosX();
	int npcPosY = npc.getPosY();
	switch (npc.getRotation())
	{

		// Nord
	case 1: if ((y == npcPosY - 1 || npcPosY - 2 || npcPosY - 3) && (x == npcPosX))
	{
		if (DEBUG)
		{
			displayStars();
			cout << "Le joueur est au nord d'un npc et < 3 cases" << endl;
			cout << "Le combat se lance" << endl;
			displayStars();
		}
		//Engage le combat
		break;
	}

			//Est
	case 2:	if ((x == npcPosX + 1 || npcPosX + 2 || npcPosX + 3) && (y == npcPosY))
	{
		if (DEBUG)
		{
			displayStars();
			cout << "Le joueur est a l'est d'un npc et < 3 cases" << endl;
			cout << "Le combat se lance" << endl;
			displayStars();
		}
		//Engage le combat
		break;
	}

			//Sud
	case 3:	if ((y == npcPosY + 1 || npcPosY + 2 || npcPosY + 3) && (x == npcPosX))
	{
		if (DEBUG)
		{
			displayStars();
			cout << "Le joueur est au sud d'un npc et < 3 cases" << endl;
			cout << "Le combat se lance" << endl;
			displayStars();
		}
		//Engage le combat
		break;
	}

			// Ouest
	case 4:if ((x == npcPosX - 1 || npcPosX - 2 || npcPosX - 3) && (y == npcPosY))
	{
		if (DEBUG)
		{
			displayStars();
			cout << "Le joueur est a l'ouest d'un npc et < 3 cases" << endl;
			cout << "Le combat se lance" << endl;
			displayStars();
		}
		//Engage le combats
		break;
	}
	}
}

/*
void world::setHerb()
{
	if (DEBUG)
	{
		displayStars();
		cout << "Debut du placement des Herbes dans le terrain de maniere aleatoire" << endl << endl;
	}
	int x = 0, y = 0;
	for (int i = 0; i < 10; i++)
	{
		do {
			x = rand() % sizeTerrain;
			y = rand() % sizeTerrain;

		} while (terrain.terrain[x][y] == '#' || 'N' || 'H');
		if (DEBUG)
		{
			cout << "Tirage de x = " << x << endl;
			cout << "Tirage de Y = " << y << endl;
			cout << "Placement de l'herbe au coordonnées : (" << x << "," << y << ")" << endl << endl;
		}
		terrain.terrain[x][y] = 'H';
	}
	if (DEBUG) displayStars();

}
*/