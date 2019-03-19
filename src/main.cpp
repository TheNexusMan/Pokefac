#include "world.h"

using namespace std;

int main(void)
{
	// terrain terrain;
	// terrain.initTerrain(1);
	// terrain.displayTerrain();

	world monde;

	cout << monde.poke[0].id << endl;
	cout << monde.poke[0].name << endl;
	cout << monde.poke[0].type << endl;
	cout << monde.poke[0].attackChoice[0].name << endl << endl;

	cout << monde.poke[1].id << endl;
	cout << monde.poke[1].name << endl;
	cout << monde.poke[1].type << endl;
	cout << monde.poke[1].attackChoice[0].name << endl << endl;

	cout << monde.poke[2].id << endl;
	cout << monde.poke[2].name << endl;
	cout << monde.poke[2].type << endl;
	cout << monde.poke[2].attackChoice[0].name << endl << endl;
	
	return 0;
}