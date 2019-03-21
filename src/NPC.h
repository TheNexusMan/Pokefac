#ifndef _NPC_H
#define _NPC_H

#include "character.h"
#include <iostream>
#include <fstream>

using namespace std;

const unsigned int NB_DIALOG = 3;

class NPC :
	public character
{
public:
	NPC();
	~NPC();
	int getRotation(); // Detecte la rotation des pnj pour la ligne (1,2 3 ou 4)
					   // 1 = Nord; 2 = Est; 3 = Sud; 4 = Ouest
	unsigned int id;
	unsigned int rotation;
	string dialog[NB_DIALOG];

private:
	


	//pokemon pokemon;
	//string dialog[];


};

#endif