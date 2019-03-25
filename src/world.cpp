#include "world.h"


world::world()
{
	initGame();
	menuOn = false;
}



void world::saveGame(string saveName)
{
	string finalPath = "./saveGames/";
	string name = finalPath + saveName + ".txt";
	mkdir(finalPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	ofstream file;
	file.open(name);
	file << saveName << "\n";
	file << mainPlayer.getPosX() << "\n";
	file << mainPlayer.getPosY() << "\n";
	file << mainPlayer.getMoney() << "\n";
	file << mainTerrain.terrainName << "\n";
	for(unsigned int i = 0; i < NBPOKEMON; i++)
	{
		file << mainPlayer.getPokemon(i).id << "\n";
		file << mainPlayer.getPokemon(i).health  << "\n"; 
		//Rajouter la save de l'expérience et du niveau quand implémenté
	}
	file.close();
			
}

void world::loadGame(string saveName)
{
	string name = "./saveGames/" + saveName + ".txt";
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
			for(unsigned int i = 0; i < NBPOKEMON; i++)
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
	} else cout << "Erreur dans l'ouverture du fichier" << endl;
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
			file >> NPCTab[i].orientation;
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

void world::initGame()
{
	initPokeTab(); //Initialisation du tableau Pok�mon
	initNPCTab(); // Initialisation du tableau NPC
	mainTerrain.initTerrain("terrain1"); // Initialisation du terrain1
	mainPlayer.initPlayer(pokeTab[0]); // Initialise le Joueur de d�part
	initDoor(); // initialisation des portes

	//DEBUG
	mainPlayer.addPokemon(pokeTab[1]);
	mainPlayer.addPokemon(pokeTab[2]);
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

void world::randomCombat(Player & mainPlayer)
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

void world::launchBattle(Player & mainPlayer, Pokemon opponentPoke, bool isAgainstPokemon)
{
	srand(time(NULL));
	Pokemon & playerPoke = mainPlayer.firstPokemonAlive();
	char attack;
	unsigned int trainerAttack;
	unsigned int numPlayerAttack;

	termClear();

	if(isAgainstPokemon) cout << "Un " << opponentPoke.name << " sauvage apparaît !" << endl;

	getchar();

	while(playerPoke.health > 0 && opponentPoke.health > 0)
	{
		do{
			termClear();

			displayOpponentsLife(mainPlayer, playerPoke, opponentPoke, isAgainstPokemon);

			cout << "Choisir l'attaque :" << endl;

			for(unsigned int i = 0; i < 4; i++)
			{
				cout << i+1 << "-" << playerPoke.attackChoice[i].name << " " << playerPoke.attackChoice[i].damagePoints << endl;
			}

			if(isAgainstPokemon) cout << "5-Fuite" << endl;

			attack = getchar();
			numPlayerAttack = attack - '0';

			if(isAgainstPokemon && (numPlayerAttack) == 5) return;

        }while((numPlayerAttack) < 1 || (numPlayerAttack) > 4);

		opponentPoke.receiveAttack(playerPoke.attackChoice[numPlayerAttack - 1]);

		termClear();

		displayOpponentsLife(mainPlayer, playerPoke, opponentPoke, isAgainstPokemon);
		cout << playerPoke.name << " attaque avec : " << playerPoke.attackChoice[numPlayerAttack - 1].name << " " << playerPoke.attackChoice[numPlayerAttack - 1].damagePoints << endl;

		if(playerPoke.health > 0 && opponentPoke.health > 0)
		{
			isAgainstPokemon ? cout << "Le pokémon sauvage" : cout << "Le dresseur";
			cout << " lance une attaque !" << endl;

			getchar();
			termClear();

			trainerAttack = rand() % 3;
			playerPoke.receiveAttack(opponentPoke.attackChoice[trainerAttack]);
			
			displayOpponentsLife(mainPlayer, playerPoke, opponentPoke, isAgainstPokemon);
			cout << opponentPoke.name << " attaque avec : " << opponentPoke.attackChoice[trainerAttack].name << " " << opponentPoke.attackChoice[trainerAttack].damagePoints << endl;

			getchar();
		}
	}

	termClear();
	displayOpponentsLife(mainPlayer, playerPoke, opponentPoke, isAgainstPokemon);

	if(playerPoke.health != 0 && isAgainstPokemon && mainPlayer.getPokeball() > 0 && mainPlayer.hasFreePokeLocation() && !mainPlayer.hasThisPokemon(opponentPoke))
	{
		mainPlayer.addPokemon(opponentPoke);
		cout << "Attrapé !:" << endl;
		mainPlayer.tabPokemon[mainPlayer.nbPokemon-1].displayInfos();

		getchar();

	}else if(playerPoke.health != 0 && !isAgainstPokemon)
	{
		cout << "Victoire !" << endl;
		mainPlayer.addMoney(100);
		cout << "Votre argent: " << mainPlayer.getMoney() << endl;

		getchar();
	}
	else if(playerPoke.health == 0){
		cout << "Défaite..." << endl;

		getchar();

		if(mainPlayer.allPokemonsAreDead())
		{
			mainPlayer.treatAllPokemon();
			teleport(mainPlayer, "house1", 8, 9);
		}
	}else{
		cout << "Victoire mais ";
		if(!mainPlayer.hasFreePokeLocation()) cout << "vous ne pouvez pas transporter de pokémon supplémentaire avec vous." << endl;
		if(mainPlayer.hasThisPokemon(opponentPoke)) cout << "vous possédez déjà ce pokémon" << endl;
		if(mainPlayer.getPokeball()== 0) cout << "vous n'avez plus de pokéball pour capturer ce pokémon" << endl;

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
	return ((x >= 0) && (x < SIZETERRAIN) && (y >= 0) && (y < SIZETERRAIN) && (mainTerrain.terrainTab[x][y] != '#') && (mainTerrain.terrainTab[x][y] != 'N'));
}

void world::isInLine(NPC npc, Player mainPlayer, const int x, const int y) const
{
	int npcPosX = npc.getPosX();
	int npcPosY = npc.getPosY();
	switch (npc.getOrientation())
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
	teleport(mainPlayer, actualDoor.terrainNameDest, actualDoor.destPosX, actualDoor.destPosY);
	}
}

Door world::whichDoor(Player mainPlayer)
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

void world::teleport(Player & mainPlayer, string terrain, unsigned int x, unsigned int y)
{
	if(terrain == mainTerrain.terrainName)
	{
		mainPlayer.setNewPos(x,y);
	}else
	{	
		mainTerrain.initTerrain(terrain);
		mainPlayer.setNewPos(x,y);
	}
}

void world::menu(bool & gameOn)
{
	int key;

	do{
		termClear();

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
				menuOn=false;
				break;

			case '3':
				loadGame("saveData");
				menuOn=false;
				break;

			case '4':
				gameOn = false;
				menuOn = false;
				break;

			case 'm':
				menuOn = false;
				break;
		
			default:
				break;
		}
	} while(menuOn);
}

void world::displayPokemon()
{
	int key;
	int keyInfoMenu;
	bool pokeMenuOn = true;
	unsigned int idPoke;
	
	do{
		termClear();

		for(unsigned int i = 0; i < NBPOKEMON; i++)
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
				menuOn = false;
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

		for(unsigned int i = 0; i < NBPOKEMON; i++)
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
		cout << "m- Fermer menu" << endl;

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
				menuOn = false;
				break;
		
			default:
				break;
		}
	} while(organiseMenuOn);
}