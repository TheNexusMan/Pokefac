#include "loopTxT.h"
#include "winTxt.h"

using namespace std;

int main(void)
{
	world mainWorld;

	// srand(time(NULL));
	// termClear();

	// txtLoop(mainWorld);
	// termClear();

	//TEST initPokeTab
	cout << mainWorld.pokeTab[0].id << endl;
	cout << mainWorld.pokeTab[0].name << endl;
	cout << mainWorld.pokeTab[0].type << endl;
	cout << mainWorld.pokeTab[0].attackChoice[0].name << endl << endl;

	cout << mainWorld.pokeTab[1].id << endl;
	cout << mainWorld.pokeTab[1].name << endl;
	cout << mainWorld.pokeTab[1].type << endl;
	cout << mainWorld.pokeTab[1].attackChoice[0].name << endl << endl;

	cout << mainWorld.pokeTab[2].id << endl;
	cout << mainWorld.pokeTab[2].name << endl;
	cout << mainWorld.pokeTab[2].type << endl;
	cout << mainWorld.pokeTab[2].attackChoice[0].name << endl << endl;

	//TEST initNPCTab
	for(unsigned int i = 0; i < NB_NPC; i++)
	{
		cout << mainWorld.NPCTab[i].id << endl;
		cout << mainWorld.NPCTab[i].name << endl;
		cout << mainWorld.NPCTab[i].getPosX() << endl;
		cout << mainWorld.NPCTab[i].getPosY() << endl;
		cout << mainWorld.NPCTab[i].nbDialog << endl;
		cout << mainWorld.NPCTab[i].NPCPokemon.name << endl;
		for(unsigned int j = 0; j < mainWorld.NPCTab[0].nbDialog; j++){
			cout << mainWorld.NPCTab[i].dialog[j] << endl;
		}
		cout << endl;
	}
	
	return 0;
}
