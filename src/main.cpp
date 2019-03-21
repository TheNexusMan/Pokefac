#include "world.h"

using namespace std;

int main(void)
{
	world mainWorld;
	//mainWorld.mainTerrain.displayTerrain(mainWorld.mainPlayer);

	/*
	//TEST initPokeTab
	cout << mainWorld.poke[0].id << endl;
	cout << mainWorld.poke[0].name << endl;
	cout << mainWorld.poke[0].type << endl;
	cout << mainWorld.poke[0].attackChoice[0].name << endl << endl;

	cout << mainWorld.poke[1].id << endl;
	cout << mainWorld.poke[1].name << endl;
	cout << mainWorld.poke[1].type << endl;
	cout << mainWorld.poke[1].attackChoice[0].name << endl << endl;

	cout << mainWorld.poke[2].id << endl;
	cout << mainWorld.poke[2].name << endl;
	cout << mainWorld.poke[2].type << endl;
	cout << mainWorld.poke[2].attackChoice[0].name << endl << endl;*/

	//TEST initNPCTab
	cout << mainWorld.NPCTab[0].id << endl;
	cout << mainWorld.NPCTab[0].name << endl;
	cout << mainWorld.NPCTab[0].getPosX() << endl;
	cout << mainWorld.NPCTab[0].getPosY() << endl;
	cout << mainWorld.NPCTab[0].nbDialog << endl;
	cout << mainWorld.NPCTab[0].dialog[0] << endl;
	cout << mainWorld.NPCTab[0].dialog[1] << endl;
	cout << endl;
	cout << mainWorld.NPCTab[1].id << endl;
	cout << mainWorld.NPCTab[1].name << endl;
	cout << mainWorld.NPCTab[1].getPosX() << endl;
	cout << mainWorld.NPCTab[1].getPosY() << endl;
	cout << mainWorld.NPCTab[1].nbDialog << endl;
	cout << mainWorld.NPCTab[1].dialog[0] << endl;
	cout << mainWorld.NPCTab[1].dialog[1] << endl;
	// for(unsigned int i = 0; i < mainWorld.NPCTab[0].nbDialog; i++){
	// 	cout << mainWorld.NPCTab[0].dialog[i] << endl;
	// }
	
	return 0;
}