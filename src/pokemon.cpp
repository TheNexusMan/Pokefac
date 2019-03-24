#include "pokemon.h"

void pokemon::receiveAttack(attack att)
{ 

	if(health > 0 && health >= att.damagePoints)
		health -= att.damagePoints;
	else if (health < att.damagePoints)
		health = 0;

}

void pokemon::displayHealth() const
{
	cout << health << "/" << maxHealth << "PV";
}

void pokemon::displayInfos() const
{
	cout << "Id: #" << id << endl;
	cout << "Name: " << name << endl;
	cout << "Type: " << type << endl;
	displayHealth();
}