#include "world.h"

world::world()
{
	ifstream fichier ("./data/pokemons.txt");

	if(fichier.is_open())
	{
		while(!fichier.eof())
		{
			for(unsigned int i = 0; i < NBPOKEMON; i++)
			{
				fichier >> poke[i].id;
				fichier >> poke[i].name;
				fichier >> poke[i].type;
				fichier >> poke[i].isFound;
				fichier >> poke[i].level;
				fichier >> poke[i].health;
				fichier >> poke[i].maxHealth;
				fichier >> poke[i].attackStat;
				fichier >> poke[i].defenseStat;
				
				for(unsigned int j = 0; j < 4; j++)
				{
					fichier >> poke[i].attackChoice[j].name;
					fichier >> poke[i].attackChoice[j].damagePoints;
				}
			}
		}

		fichier.close();
	}else{
		cout << "Erreur d'ouverture du fichier pokemons" << endl;
	}
}