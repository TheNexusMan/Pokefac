#include "world.h"

using namespace std;

int main(void)
{
	// terrain terrain;
	// terrain.initTerrain(1);
	// terrain.displayTerrain();

	world mainWorld;

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
	cout << mainWorld.poke[2].attackChoice[0].name << endl << endl;
	
	return 0;
}