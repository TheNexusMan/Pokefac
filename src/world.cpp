#include "world.h"


world::world()
{
	initPokeTab(); //Initialisation du tableau Pok�mon
	initNPCTab(); // Initialisation du tableau NPC
	mainTerrain.initTerrain(1, "terrain1");
	mainPlayer.initPlayer(pokeTab[0]); // Initialise le Joueur de d�part
	initDoor();
}

void world::initDoor()
{
	ifstream file("./data/doors.txt");

	if(file.is_open())
	{
		while(!file.eof())
		{
			for(unsigned int i = 0; i < NB_DOOR; i++)
			{
				file >> doors[i].id;
				file >> doors[i].posX;
				file >> doors[i].posY;
				file >> doors[i].destPosX;
				file >> doors[i].destPosY;
				file >> doors[i].terrainNamePos;
				file >> doors[i].terrainNameDest;
			}
		}
		file.close();
	}
	else cout << "Erreur dans l'ouverture du fichier" << endl;

	
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

void world::randomCombat(player & mainPlayer)
{
	unsigned int random = randomNumber();
	if ((isInHerb(mainPlayer.getPosX(), mainPlayer.getPosY()) && (random % 5 == 0)))
	{
		if (DEBUG)
		{
			displayStars();
			cout << "Le joueur est dans l'herbe et la condition s'avere juste" << endl;
			cout << "randomNumber() = " << random << " Random % 5 == 0" << endl;
			cout << "Lancement du combat" << endl;
			displayStars();

		}
		unsigned int randomPoke = rand() % 3;
		launchBattle(mainPlayer, pokeTab[randomPoke], true);
	}
}

bool world::isInHerb(const int x, const int y) const
{
	return (mainTerrain.terrainTab[x][y] == 'H');
}

void world::launchBattle(player & mainPlayer, pokemon poke, bool isAgainstPokemon)
{
	srand(time(NULL));
	char attack;
	int trainerAttack;

	termClear();

	if(isAgainstPokemon) cout << "A wild " << poke.name << " appears!" << endl;

	getchar();

	while(mainPlayer.tabPokemon[0].health > 0 && poke.health > 0)
	{
		do{
			termClear();

			displayOpponentsLife(mainPlayer, poke, isAgainstPokemon);

			cout << "Choose your attack :" << endl;

			for(unsigned int i = 0; i < 4; i++)
			{
				cout << i+1 << "-" << mainPlayer.tabPokemon[0].attackChoice[i].name << " " << mainPlayer.tabPokemon[0].attackChoice[i].damagePoints << endl;
			}

			if(isAgainstPokemon) cout << "5-Escape" << endl;

			attack = getchar();

			if(isAgainstPokemon && (attack - '0') == 5) return;

        }while((attack - '0') < 1 || (attack - '0') > 4);

		poke.receiveAttack(poke, mainPlayer.tabPokemon[0].attackChoice[attack - '0' - 1]);

		termClear();

		displayOpponentsLife(mainPlayer, poke, isAgainstPokemon);
		cout << mainPlayer.tabPokemon[0].name << " attacks with: " << mainPlayer.tabPokemon[0].attackChoice[attack - '0' - 1].name << " " << mainPlayer.tabPokemon[0].attackChoice[attack - '0' - 1].damagePoints << endl;

		if(mainPlayer.tabPokemon[0].health > 0 && poke.health > 0)
		{
			isAgainstPokemon ? cout << "The wild Pokemon attacks you!" << endl : cout << "The Trainer attacks you!" << endl;

			getchar();
			termClear();

			trainerAttack = rand() % 3;
			mainPlayer.tabPokemon[0].receiveAttack(mainPlayer.tabPokemon[0], poke.attackChoice[trainerAttack]);
			
			displayOpponentsLife(mainPlayer, poke, isAgainstPokemon);
			cout << poke.name << " attacks with: " << poke.attackChoice[trainerAttack].name << " " << poke.attackChoice[trainerAttack].damagePoints << endl;

			getchar();
		}
	}

	termClear();
	displayOpponentsLife(mainPlayer, poke, isAgainstPokemon);

	if(mainPlayer.tabPokemon[0].health != 0 && isAgainstPokemon && mainPlayer.getPokeball() > 0 && mainPlayer.hasFreePokeLocation() && !mainPlayer.hasThisPokemon(poke))
	{
		mainPlayer.addPokemon(poke);
		cout << "You've captured:" << endl;
		mainPlayer.tabPokemon[mainPlayer.nbPokemon-1].displayInfos();

		getchar();

	}else if(mainPlayer.tabPokemon[0].health != 0 && !isAgainstPokemon)
	{
		cout << "You win the fight!" << endl;
		mainPlayer.addMoney(100);
		cout << "Your money: " << mainPlayer.getMoney() << endl;

		getchar();
	}
	else if(mainPlayer.tabPokemon[0].health == 0){
		cout << "You loose" << endl;

		getchar();
	}else{
		cout << "You win but ";
		if(!mainPlayer.hasFreePokeLocation()) cout << "you can't carry another Pokémon with you." << endl;
		if(mainPlayer.hasThisPokemon(poke)) cout << "you already have this Pokémon" << endl;
		if(mainPlayer.getPokeball()== 0) cout << "you don't have Pokéball to capture this Pokémon" << endl;

		getchar();
	}
	mainPlayer.tabPokemon[0].health = mainPlayer.tabPokemon[0].maxHealth;
}

void world::displayOpponentsLife(const player mainPlayer, const pokemon poke, const bool isAgainstPokemon) const
{
	cout << "Your Pokémon: " << mainPlayer.tabPokemon[0].name << " ";
	mainPlayer.tabPokemon[0].displayHealth();
	cout << endl;
	isAgainstPokemon ? cout << "Wild pokémon: " : cout << "Opponent Pokémon: ";
	cout << poke.name << " ";
	poke.displayHealth();
	cout << endl << "---------------------------------" << endl << endl;
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


void world::door()
{
	if(mainTerrain.terrainTab[mainPlayer.getPosX()][mainPlayer.getPosY()] == 'O')
	{
	Door actualDoor = whichDoor(mainPlayer);
	teleport(mainPlayer, actualDoor.id, actualDoor.terrainNameDest, actualDoor.destPosX, actualDoor.destPosY);
	}
}

Door world::whichDoor(player mainPlayer)
{
	Door returnedDoor;
	for(unsigned int i = 0; i < NB_DOOR; i++)
	{
		if((mainPlayer.getPosX() == doors[i].posX) && (mainPlayer.getPosY() == doors[i].posY) && mainTerrain.terrainName == doors[i].terrainNamePos)
		{
			 returnedDoor = doors[i];
		} 
	} 
	return returnedDoor;
}

void world::teleport(player & mainPlayer,unsigned int id, string terrain, unsigned int x, unsigned int y)
{
	if(terrain == mainTerrain.terrainName)
	{
		mainPlayer.setNewPos(x,y);
	}else
	{	
		mainTerrain.initTerrain(id, terrain);
		mainPlayer.setNewPos(x,y);

	}

}