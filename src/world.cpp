#include "world.h"


world::world()
{
	initGame();
}

void write_to_log_file(string text) //to_string(valeur);
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	string finalPath = "./data/logs/";
	string name = finalPath + "logs.txt";
	mkdir(finalPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	ofstream file;
	file.open(name, ofstream::app);
	file << "[" << 1900 + ltm->tm_year << "/" << 1+ ltm->tm_mon << "/" << ltm->tm_mday << ":" << ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << "] : ";
	file << text << "\n";
	file.close();

}

void world::saveGame(string saveName)
{
	isSaving = true;
	string finalPath = "./data/saveGames/";
	string name = finalPath + saveName + ".txt";
	mkdir(finalPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	ofstream file;
	file.open(name);
	file << saveName << "\n";
	file << mainPlayer.getPosX() << "\n";
	file << mainPlayer.getPosY() << "\n";
	file << mainPlayer.getMoney() << "\n";
	file << mainTerrain.terrainName << "\n";
	for(unsigned int i = 0; i < NBPLAYERPOKEMON; i++)
	{
		file << mainPlayer.getPokemon(i).id << "\n";
		file << mainPlayer.getPokemon(i).health  << "\n"; 
		//Rajouter la save de l'expérience et du niveau quand implémenté
	}
	file.close();		
}

void world::loadGame(string saveName) 
{
	isLoading = true;
	string name = "./data/saveGames/" + saveName + ".txt";
	ifstream file(name);
	unsigned int posX, posY, cash;
	string nameTerrain;
	if(file.is_open())
	{
		while(!file.eof())
		{
			file >> gameSaveName;
			file >> posX;
			file >> posY;
			file >> cash;
			file >> nameTerrain;
			for(unsigned int i = 0; i < NBPLAYERPOKEMON; i++)
			{
				file >> mainPlayer.getPokemon(i).id;
				file >> mainPlayer.getPokemon(i).health;
				//Rajouter le chargement de l'expérience et du niveau quand implémenté
			}		
		}
		mainTerrain.initTerrain(nameTerrain);
		mainPlayer.setNewPos(posX, posY);
		mainPlayer.addMoney(cash);
		file.close();
	} else write_to_log_file("WARNING : Erreur dans l'ouverture du fichier ./data/saveGames/" + saveName + ".txt");

	mainTerrain.initTerrain(nameTerrain);
	mainPlayer.setNewPos(posX, posY);
	mainPlayer.addMoney(cash);
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
				file >> doors[i].posX;
				file >> doors[i].posY;
				file >> doors[i].destPosX;
				file >> doors[i].destPosY;
				file >> doors[i].orientation;
				file >> doors[i].terrainNamePos;
				file >> doors[i].terrainNameDest;
			}
		}
		file.close();
	}
	else write_to_log_file("WARNING : Erreur dans l'ouverture du fichier ./data/doors.txt");
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
				file >> pokeTab[i].namePic;

				for (unsigned int j = 0; j < 4; j++)
				{
					file >> pokeTab[i].attackChoice[j].name;
					file >> pokeTab[i].attackChoice[j].damagePoints;
				}
			}
		}
		file.close();
	}
	else write_to_log_file("WARNING : Erreur dans l'ouvertur du fichier ./data/pokemons.txt");
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
		char orientation;

		while (!file.eof() && i < NB_NPC)
		{
			file >> NPCTab[i].id;
			file >> NPCTab[i].name;
			file >> pos;
			NPCTab[i].setPosX(pos);
			file >> pos;
			NPCTab[i].setPosY(pos);
			file >> orientation;
			NPCTab[i].setOrientation(orientation);
			file >> NPCTab[i].terrainName;
			file >> idPokemon;
			NPCTab[i].NPCPokemon = pokeTab[idPokemon];
			file >> NPCTab[i].nbDialog;
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
	else write_to_log_file("WARNING : Erreur dans l'ouverture du fichier ./data/NPCs.txt");
}


void world::logFilesStart() const
{
	write_to_log_file("****************************************");
	write_to_log_file("Lancement du programme");
	write_to_log_file("Des informations suplementaires seront affichees dans le fichier ./data/logs.txt");
	write_to_log_file("****************************************");

}

void world::initGame()
{
	logFilesStart();
	initPokeTab(); //Initialisation du tableau Pok�mon
	initNPCTab(); // Initialisation du tableau NPC
	mainTerrain.initTerrain("terrain1"); // Initialisation du terrain1
	initTerrainNPC("terrain1"); // Initialise les cases d'intéraction avec les NPC
	mainPlayer.initPlayer(pokeTab[0]); // Initialise le Joueur de départ
	initDoor(); // Initialisation des portes

	mainPlayer.addPokemon(pokeTab[1]);
}

int world::randomNumber()
{
	int random = rand() % 100;
	write_to_log_file("Nombre aleatoire genere par randomNumber() => " + to_string(random));
	return random;
}

void world::randomCombat(Player & mainPlayer)
{		

	if ((isInHerb(mainPlayer.getPosX(), mainPlayer.getPosY())))
	{
		unsigned int random = randomNumber();
		if(random % 5 == 0)
		{
			
		write_to_log_file("Le joueur est dans l'herbe et la condition s'avere juste");
		write_to_log_file("randomNumber() = " + to_string(random) + " Random % 5 == 0");
	    write_to_log_file("Lancement du combat");

		unsigned int randomPoke = rand() % NBPOKEMON;
		battle(mainPlayer, pokeTab[randomPoke], true);
		}
	}
}

bool world::isInHerb(const int x, const int y) const
{
	return (mainTerrain.terrainTab[x][y] == 'H');
}

void world::healAll(Player & mainPlayer)
{
	if(isOnHeal(mainPlayer.getPosX(), mainPlayer.getPosY()))
	{
		mainPlayer.treatAllPokemon();
		write_to_log_file("Le joueur est sur une case de soin");
		write_to_log_file("Les pokémons du joueur on été soignés");
	}
}

bool world::isOnHeal(const int x, const int y) const
{
	return(mainTerrain.terrainTab[x][y] == 'V');
}

void world::battle(Player & mainPlayer, Pokemon opponentPoke, bool isAgainstPokemon)
{
	srand(time(NULL));
	Pokemon * playerPoke = &mainPlayer.firstPokemonAlive();
	bool menuBool = false;
	char attack;
	unsigned int numPlayerAttack;
	unsigned int trainerAttack;

	termClear();

	if(isAgainstPokemon) cout << "Un " << opponentPoke.name << " sauvage apparaît !" << endl;

	getchar();

	while(playerPoke->health > 0 && opponentPoke.health > 0)
	{
		do{
			termClear();

			displayOpponentsLife(mainPlayer, *playerPoke, opponentPoke, isAgainstPokemon);

			cout << "Choisir l'attaque :" << endl;

			for(unsigned int i = 0; i < 4; i++)
			{
				cout << i+1 << "-" << playerPoke->attackChoice[i].name << " " << playerPoke->attackChoice[i].damagePoints << endl;
			}
			cout << endl << "5-Changer de pokémon" << endl;
			if(isAgainstPokemon) cout << "6-Fuite" << endl;

			attack = getchar();
			numPlayerAttack = attack - '0';

			if(isAgainstPokemon && (numPlayerAttack == 6)) return;

        }while((numPlayerAttack < 1) || (numPlayerAttack > 5));

		if(numPlayerAttack == 5)
		{
			unsigned int idOldPoke = playerPoke->id;
			organisePokemon(menuBool);

			if(idOldPoke != mainPlayer.firstPokemonAlive().id)
			{
				playerPoke = &mainPlayer.firstPokemonAlive();
				termClear();
				cout << mainPlayer.firstPokemonAlive().name << " est envoyé sur le terrain !" << endl;
				getchar();
			}
		}else{
			termClear();

			opponentPoke.receiveAttack(playerPoke->attackChoice[numPlayerAttack - 1]);
			displayOpponentsLife(mainPlayer, *playerPoke, opponentPoke, isAgainstPokemon);
			cout << playerPoke->name << " attaque avec : " << playerPoke->attackChoice[numPlayerAttack - 1].name << " " << playerPoke->attackChoice[numPlayerAttack - 1].damagePoints << endl;
			
			getchar();
		}
	


		if(opponentPoke.health > 0)
		{
			termClear();
			
			isAgainstPokemon ? cout << "Le pokémon sauvage" : cout << "Le dresseur";
			cout << " lance une attaque !" << endl;

			getchar();
			termClear();

			trainerAttack = rand() % 3;
			playerPoke->receiveAttack(opponentPoke.attackChoice[trainerAttack]);
			
			displayOpponentsLife(mainPlayer, *playerPoke, opponentPoke, isAgainstPokemon);
			cout << opponentPoke.name << " attaque avec : " << opponentPoke.attackChoice[trainerAttack].name << " " << opponentPoke.attackChoice[trainerAttack].damagePoints << endl;

			getchar();
		}

		if(playerPoke->health <= 0 && !mainPlayer.allPokemonsAreDead())
		{
			cout << playerPoke->name << " est KO, choisir un autre pokémon" << endl;
			getchar();
			organisePokemon(menuBool);
			playerPoke = &mainPlayer.firstPokemonAlive();
		}
	}

	termClear();
	displayOpponentsLife(mainPlayer, *playerPoke, opponentPoke, isAgainstPokemon);

	if(playerPoke->health != 0 && isAgainstPokemon && mainPlayer.getPokeball() > 0 && mainPlayer.hasFreePokeLocation() && !mainPlayer.hasThisPokemon(opponentPoke))
	{
		mainPlayer.addPokemon(opponentPoke);
		cout << "Attrapé !:" << endl;
		mainPlayer.tabPokemon[mainPlayer.nbPokemon-1].displayInfos();
		mainPlayer.usePokeball();

		getchar();

	}else if(playerPoke->health != 0 && !isAgainstPokemon)
	{
		cout << "Victoire !" << endl;
		mainPlayer.addMoney(100);
		cout << "Votre argent: " << mainPlayer.getMoney() << endl;

		getchar();
	}
	else if(playerPoke->health == 0){
		cout << "Défaite..." << endl;

		getchar();

		if(mainPlayer.allPokemonsAreDead())
		{
			mainPlayer.treatAllPokemon();
			teleport(mainPlayer, "house1", 8, 9);
			write_to_log_file("Tous les pokemons sont mort téléportation du joueurs dans le terrain house1 aux coordonnées (8,9)");
		}
	}else{
		cout << "Victoire mais ";
		if(mainPlayer.hasThisPokemon(opponentPoke)) cout << "vous possédez déjà ce pokémon" << endl;
		if(!mainPlayer.hasFreePokeLocation() && !mainPlayer.hasThisPokemon(opponentPoke)) cout << "vous ne pouvez pas transporter de pokémon supplémentaire avec vous." << endl;
		if(mainPlayer.getPokeball() == 0 && !mainPlayer.hasThisPokemon(opponentPoke) && mainPlayer.hasFreePokeLocation()) cout << "vous n'avez plus de pokéball pour capturer ce pokémon" << endl;

		getchar();
	}
}

void world::displayOpponentsLife(const Player mainPlayer, const Pokemon playerPoke, const Pokemon opponentPoke, const bool isAgainstPokemon) const
{
	cout << "Joueur : " << playerPoke.name << " ";
	playerPoke.displayHealth();
	cout << endl;
	cout << "Adversaire : " << opponentPoke.name << " ";
	opponentPoke.displayHealth();
	cout << endl;
	cout << "---------------------------------" << endl << endl;
}

bool world::moveIsAllowed(Player mainPlayer, const int x, const int y) const
{
	return ((x >= 0) && (x < SIZETERRAIN) && (y >= 0) && (y < SIZETERRAIN) && (mainTerrain.terrainTab[x][y] != '#') && (mainTerrain.terrainTab[x][y] != 'N') && (mainTerrain.terrainTab[x][y] != '*'));
}

void world::door()
{
	if(mainTerrain.terrainTab[mainPlayer.getPosX()][mainPlayer.getPosY()] == 'O')
	{
		Door actualDoor = whichDoor(mainPlayer.getPosX(), mainPlayer.getPosY());
		teleport(mainPlayer, actualDoor.terrainNameDest, actualDoor.destPosX, actualDoor.destPosY);
		write_to_log_file("Changement de terrain : " + actualDoor.terrainNameDest + " Nouvelle position du joueur : (" + to_string(actualDoor.destPosX) + "," + to_string(actualDoor.destPosY) +")");
	}
}

Door world::whichDoor(unsigned int x, unsigned int y)
{
	Door returnedDoor;
	for(unsigned int i = 0; i < NB_DOOR; i++)
	{
		if((x == doors[i].posX) && (y == doors[i].posY) && mainTerrain.terrainName == doors[i].terrainNamePos)
		{
			 returnedDoor = doors[i];
		} 
	} 
	return returnedDoor;
}

NPC* world::whichNPC(Player & mainPlayer)
{
	unsigned int PlayerPosX = mainPlayer.getPosX();
	unsigned int PlayerPosY = mainPlayer.getPosY();

	for (unsigned int i=0; i < NB_NPC; i++)
	{
		if(NPCTab[i].terrainName == mainTerrain.terrainName)
		{
			switch (NPCTab[i].getOrientation())
			{

				// Ouest
				case 'o': 
					if ((PlayerPosY == NPCTab[i].getPosY() - 1 || NPCTab[i].getPosY() - 2 || NPCTab[i].getPosY() - 3) && (PlayerPosX == NPCTab[i].getPosX()))
					{
						return &NPCTab[i];
						break;
					}

				// Sud
				case 's': 
					if ((PlayerPosX == NPCTab[i].getPosX() + 1 || NPCTab[i].getPosX() + 2 || NPCTab[i].getPosX() + 3) && (PlayerPosY == NPCTab[i].getPosY()))
					{
						return &NPCTab[i];
						break;
					}

				// Est
				case 'e':
					if ((PlayerPosY == NPCTab[i].getPosY() + 1 || NPCTab[i].getPosY() + 2 || NPCTab[i].getPosY() + 3) && (PlayerPosX == NPCTab[i].getPosX()))
					{
						return &NPCTab[i];
						break;
					}

				// Nord
				case 'n': 
					if ((PlayerPosX == NPCTab[i].getPosX() - 1 || NPCTab[i].getPosX() - 2 || NPCTab[i].getPosX() - 3) && (PlayerPosY == NPCTab[i].getPosY()))
					{
						return &NPCTab[i];
						break;
					}
				default :
					break;
			}
		}
	}

	return NULL;
}

void world::initTerrainNPC(string terrain)
{
	for (unsigned int i=0; i < NB_NPC; i++)
	{
		if (NPCTab[i].terrainName == terrain)
		{
			switch (NPCTab[i].getOrientation())
			{

				// Ouest
				case 'o': 
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()-1] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()-1]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()-2] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()-2]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()-3] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()-3]='-';
					break;

				// Sud
				case 's': 
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()+1][NPCTab[i].getPosY()] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()+1][NPCTab[i].getPosY()]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()+2][NPCTab[i].getPosY()] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()+2][NPCTab[i].getPosY()]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()+3][NPCTab[i].getPosY()] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()+3][NPCTab[i].getPosY()]='-';
					break;

				// Est
				case 'e': 
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()+1] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()+1]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()+2] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()+2]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()+3] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()][NPCTab[i].getPosY()+3]='-';
					break;

				// Nord
				case 'n':
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()-1][NPCTab[i].getPosY()] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()-1][NPCTab[i].getPosY()]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()-2][NPCTab[i].getPosY()] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()-2][NPCTab[i].getPosY()]='-';
					if (mainTerrain.terrainTab[NPCTab[i].getPosX()-3][NPCTab[i].getPosY()] == '.') mainTerrain.terrainTab[NPCTab[i].getPosX()-3][NPCTab[i].getPosY()]='-';
					break;

				default :
					break;
			}
		}
	}
}

void world::NPCBattle()
{
	if (mainTerrain.terrainTab[mainPlayer.getPosX()][mainPlayer.getPosY()] == '-')
	{
		termClear();
		NPC * npc = whichNPC(mainPlayer);
		if (npc->beaten == 0) 
		{
			cout<<npc->id;
			getchar();
			//battle();
		}
		else{
			cout<<"Tu as déjà battu ce champion d'arène ! ";
			getchar();
		} 
	} 
}

void world::teleport(Player & mainPlayer, string terrain, unsigned int x, unsigned int y)
{
	if(terrain != mainTerrain.terrainName)
	{
		mainTerrain.initTerrain(terrain);
		initTerrainNPC(terrain);
	}
	mainPlayer.setNewPos(x,y);
}

void world::menu(bool & gameOn)
{
	int key;
	do{
		//termClear();

		cout << "1- Pokémons" << endl;
		cout << "2- Sauvegarde" << endl;
		cout << "3- Charger" << endl;
		cout << "4- Quitter le jeu" << endl;
		cout << endl;
		cout << "m- Fermer menu" << endl;

		key = getchar();

		switch (key)
		{
			case '1':
				displayPokemon();
				break;

			case '2':
				saveGame("saveData");
				write_to_log_file("Game Saved to ./data/saveGames/saveData.txt");
				menuOn=0;
				break;

			case '3':
				loadGame("saveData");
				write_to_log_file("Game loaded from ./data/saveGames/saveData.txt");
				menuOn=0;
				break;

			case '4':
				gameOn = false;
				menuOn = 0;
				break;

			case 'm':
				menuOn = 0;
				break;
		
			default:
				break;
		}
	} while(menuOn == 1);
}

void world::displayPokemon()
{
	int key;
	int keyInfoMenu;
	bool pokeMenuOn = true;
	unsigned int idPoke;
	
	do{
		termClear();

		for(unsigned int i = 0; i < NBPLAYERPOKEMON; i++)
		{
			if(i < mainPlayer.nbPokemon)
			{
				cout << i+1 << "- " << mainPlayer.getPokemon(i).name << " ";
				mainPlayer.getPokemon(i).displayHealth();
				cout << endl;
			}else{
				cout << i+1 << "-" << endl;
			}
		}
		
		cout << endl;
		cout << "o- Organiser" << endl;
		cout << "r- Retour" << endl;
		cout << "m- Fermer menu" << endl;

		key = getchar();
		idPoke = key - '0';

		if(idPoke > 0 && idPoke <= mainPlayer.nbPokemon)
		{
			termClear();
			mainPlayer.getPokemon(idPoke - 1).displayInfos();
			keyInfoMenu = getchar();
			if(keyInfoMenu == 'm') key = 'm';
		}

		switch (key)
		{		
			case 'o':
				organisePokemon(pokeMenuOn);
				break;

			case 'r':
				pokeMenuOn = false;
				break;

			case 'm':
				pokeMenuOn = false;
				menuOn = 0;
				break;
		
			default:
				break;
		}

	} while(pokeMenuOn);
}

void world::organisePokemon(bool & pokeMenuOn)
{
	int key;
	bool organiseMenuOn = true;
	unsigned int indice = 0;
	bool isTaken = false;

	do{
		termClear();

		for(unsigned int i = 0; i < mainPlayer.nbPokemon; i++)
		{
			if(i < mainPlayer.nbPokemon && indice == i && isTaken)
			{
				cout << "-  " << mainPlayer.getPokemon(i).name << " ";
				mainPlayer.getPokemon(i).displayHealth();
				cout << endl;
			}else if(i < mainPlayer.nbPokemon && indice == i)
			{
				cout << "-" << mainPlayer.getPokemon(i).name << " ";
				mainPlayer.getPokemon(i).displayHealth();
				cout << endl;
			}else{
				cout << " " << mainPlayer.getPokemon(i).name << " ";
				mainPlayer.getPokemon(i).displayHealth();
				cout << endl;
			}
		}

		cout << endl;
		cout << "p- Prendre / déposer" << endl;
		cout << "z/s- Monter / descendre" << endl;
		cout << endl;
		cout << "r- Retour" << endl;
		if(pokeMenuOn){
			cout << "m- Fermer menu" << endl;
		}

		key = getchar();

		switch (key)
		{		
			case 's':
				if(indice < mainPlayer.nbPokemon-1){
					indice++;
					if(isTaken) mainPlayer.changePlacePoke(indice-1, indice);
				}
				break;

			case 'z':
				if(indice > 0){
					indice--;
					if(isTaken) mainPlayer.changePlacePoke(indice+1, indice);
				}
				break;

			case 'p':
				isTaken = !isTaken;
				break;

			case 'r':
				organiseMenuOn = false;
				break;

			case 'm':
				organiseMenuOn = false;
				pokeMenuOn = false;
				menuOn = 0;
				break;
		
			default:
				break;
		}
	} while(organiseMenuOn);
}