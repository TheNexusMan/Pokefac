#include "terrain.h"

using namespace std;

void terrain::initTerrain(int idTerrain)
{
	ifstream fichier ("./data/terrain1.txt");

	if(fichier.is_open())
	{
		string ligne;
		int i = 0;
		while(!fichier.eof())
		{
			getline(fichier, ligne);
			
			for(unsigned int j = 0; j < ligne.length(); j++)
			{

				if (ligne[j] != ' ') {
					terrain[i][(int) j / 2] = ligne[j];
				}
			}
			i++;
		}

		fichier.close();
	}else{
		cout << "Erreur d'ouverture du terrain" << idTerrain << endl;
	}
}

void terrain::displayTerrain()
{
	for(int i = 0; i < sizeTerrain; i++)
	{
		for(int j = 0; j < sizeTerrain; j++)
		{
			cout << terrain[i][j] << " ";
		}
		cout << endl;
	}
}