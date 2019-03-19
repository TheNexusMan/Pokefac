#include <iostream>
#include <stdlib.h>

using namespace std;

world::world()
{
	ifstream fichier ("./data/pokemons.txt");

	if(fichier.is_open())
	{

		string ligne;
		int i = 0;
		while(!fichier.eof())
		{
			for(unsigned int i = 0; i < NBPOKEMON; i++)
			{
				poke[i].id << fichier;
				poke[i].name << fichier;
				poke[i].type << fichier;
				poke[i].isfound << fichier;
				poke[i].level << fichier;
				poke[i].health << fichier;
				poke[i].maxhealth << fichier;
				poke[i].attackStat << fichier;
				poke[i].defenseStat << fichier;
				
				for(unsigned int i = 0; i < 4; i++)
				{
					attack[i].name << fichier;
					attack[i].damagePoints << fichier;
				}
			}
		}

		fichier.close();
	}else{
		cout << "Erreur d'ouverture du terrain" << idTerrain << endl;
	}
}