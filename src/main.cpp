#include "world.h"

using namespace std;

int main(void)
{
	// terrain terrain;
	// terrain.initTerrain(1);
	// terrain.displayTerrain();

	world world;

	cout << world.poke[0].id << endl;
	cout << world.poke[0].name << endl;
	cout << world.poke[0].type << endl;
	cout << world.poke[0].attack[0].name << endl << endl;

	cout << world.poke[1].id << endl;
	cout << world.poke[1].name << endl;
	cout << world.poke[1].type << endl;
	cout << world.poke[1].attack[0].name << endl << endl;

	cout << world.poke[1].id << endl;
	cout << world.poke[1].name << endl;
	cout << world.poke[1].type << endl;
	cout << world.poke[1].attack[0].name << endl << endl;
	
	return 0;
}