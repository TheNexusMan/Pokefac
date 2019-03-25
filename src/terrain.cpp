#include "terrain.h"

terrain::terrain(){
	
}

void terrain::initTerrain(string nameTerrain)
{
	terrainName = nameTerrain;
	string path = "./data/" + nameTerrain + ".txt";
	ifstream fichier (path);

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
		cout << "Erreur d'ouverture du terrain : " << nameTerrain << endl;
	}
}

void terrain::displayTerrain(Player mainPlayer)
{
	for(unsigned int i = 0; i < SIZETERRAIN; i++)
	{
		for(unsigned int j = 0; j < SIZETERRAIN; j++)
		{
			if((mainPlayer.getPosX() == i) && (mainPlayer.getPosY() == j)){
				cout << 'P' << ' ';
			}else{
				cout << terrainTab[i][j] << " ";
			}
		}
		cout << endl;
	}
}