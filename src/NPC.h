#pragma once
#include "character.h"
#include "player.h"
class NPC :
	public character
{
public:
	NPC();
	~NPC();

private:
	

	unsigned int id;
	unsigned int rotation;
	//pokemon pokemon;
	//string dialog[];


	void setRotation(unsigned int nb);
	int getRotation(); // Detecte la rotation des pnj pour la ligne (1,2 3 ou 4)
					   // 1 = Nord; 2 = Est; 3 = Sud; 4 = Ouest
	void checkLine(unsigned int x, unsigned int y, player playerOne); //Verifie les lignes => lance le combat si collision


};

