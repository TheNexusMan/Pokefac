#include "terrain.h"

terrain::terrain(){
	
}

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
					terrainTab[i][(int) j / 2] = ligne[j];
				}
			}
			i++;
		}

		fichier.close();
	}else{
		cout << "Erreur d'ouverture du terrain" << idTerrain << endl;
	}
}

void terrain::displayTerrain(player mainPlayer)
{
	for(unsigned int i = 0; i < SIZETERRAIN; i++)
	{
		for(unsigned int j = 0; j < SIZETERRAIN; j++)
		{
			//cout << mainPlayer.getPosX() << " " << mainPlayer.getPosY() << endl;
			if((i == mainPlayer.getPosX() ) && (j == mainPlayer.getPosY())){
				cout << 'P' << ' ';
			}else{
				cout << terrainTab[i][j] << " ";
			}
		}
		cout << endl;
	}
}