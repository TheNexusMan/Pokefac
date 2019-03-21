#include "world.h"


world::world()
{
	initPokeTab(); //Initialisation du tableau Pok�mon
	initNPCTab(); // Initialisation du tableau NPC
	//initPlayer(mainPlayer); // Initialise le Joueur de d�part
	mainPlayer.initPlayer();
	mainTerrain.initTerrain(1);
	randomNumber();
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
				file >> pokeTab[i].id;
				file >> pokeTab[i].name;
				file >> pokeTab[i].type;
				file >> pokeTab[i].isFound;
				file >> pokeTab[i].level;
				file >> pokeTab[i].health;
				file >> pokeTab[i].maxHealth;
				file >> pokeTab[i].attackStat;
				file >> pokeTab[i].defenseStat;

				for (unsigned int j = 0; j < 4; j++)
				{
					file >> pokeTab[i].attackChoice[j].name;
					file >> pokeTab[i].attackChoice[j].damagePoints;
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
	ifstream file("./data/NPCs.txt");
	if (file.is_open())
	{
		unsigned int pos;
		string sentence;
		unsigned int idPokemon;
		unsigned int i = 0;

		while (!file.eof() && i < NB_NPC)
		{
			file >> NPCTab[i].id;
			file >> NPCTab[i].name;
			file >> pos;
			NPCTab[i].setPosX(pos);
			file >> pos;
			NPCTab[i].setPosY(pos);
			file >> NPCTab[i].rotation;
			file >> NPCTab[i].nbDialog;
			file >> idPokemon;
			NPCTab[i].NPCPokemon.initPokemon(pokeTab[idPokemon]);
			getline(file, sentence);

			for(unsigned int j = 0; j < NPCTab[i].nbDialog; j++)
			{
				getline(file, sentence);
				NPCTab[i].dialog[j] = sentence;
			}
			i++;
		}
		file.close();
	}
	else {
		cout << "Erreur dans l'ouverture du fichier ./data/NPCs.txt" << endl;
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
	int random = rand() % 100;
	if (DEBUG)
	{
		cout << "Nombre aleatoire genere par randomNumber() => " << random << endl;
	}
	return random;

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
		cout << "Yeah" << endl;
		//Lance le combat
	} //Sinon rien
}

bool world::isInHerb(player mainPlayer, const int x, const int y) const
{
	return (mainTerrain.terrainTab[x][y] == 'H');
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
	case 'n': if ((y == npcPosY - 1 || npcPosY - 2 || npcPosY - 3) && (x == npcPosX))
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
	case 'e':	if ((x == npcPosX + 1 || npcPosX + 2 || npcPosX + 3) && (y == npcPosY))
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
	case 's':	if ((y == npcPosY + 1 || npcPosY + 2 || npcPosY + 3) && (x == npcPosX))
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
	case 'o':if ((x == npcPosX - 1 || npcPosX - 2 || npcPosX - 3) && (y == npcPosY))
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
			x = rand() % SIZETERRAIN;
			y = rand() % SIZETERRAIN;

		} while (mainTerrain.terrain[x][y] == '#' || 'N' || 'H');
		if (DEBUG)
		{
			cout << "Tirage de x = " << x << endl;
			cout << "Tirage de Y = " << y << endl;
<<<<<<< HEAD
			cout << "Placement de l'herbe au coordonn�es : (" << x << "," << y << ")" << endl << endl;
=======
			cout << "Placement de l'herbe au coordonn�es : (" << x << "," << y << ")" << endl << endl;
>>>>>>> arnaud
		}
		mainTerrain.terrain[x][y] = 'H';
	}
	if (DEBUG) displayStars();

}
*/