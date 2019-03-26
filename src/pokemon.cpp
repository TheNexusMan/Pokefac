#include "pokemon.h"

void Pokemon::receiveAttack(attack att)
{ 

	if(health > 0 && health >= att.damagePoints)
		health -= att.damagePoints;
	else if (health < att.damagePoints)
		health = 0;

}

void Pokemon::displayHealth() const
{
	cout << health << "/" << maxHealth << "PV";
}

void Pokemon::displayInfos() const
{
	cout << "Id : #" << id << endl;
	cout << "Nom : " << name << endl;
	cout << "Type : " << type << endl;
	cout << "Vie : ";
	displayHealth();
	cout << endl << endl;;
	cout << "Attaques :" << endl;
	cout << "Nom     Puissance" << endl;
	for(unsigned int i = 0; i < 4; i++)
	{
		cout << attackChoice[i].name << "       " << attackChoice[i].damagePoints << endl;
	}
}