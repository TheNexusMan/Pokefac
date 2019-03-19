#include "attack.h"
#include "pokemon.h"
#include "battle.cpp"
#include "player.cpp"
#include <iostream>
using namespace std

battle:: launchBattle(player play1, pokemon poke)
{
	srand(time(NULL));

	while(play1.tabPokemon[0].health > 0 || poke.health > 0)
	do {
		int a; 
		cout<<"The trainer's pokemon health : "<<poke.health<<endl;
		cout<<"Your pokemon health : "<<play1.tabPokemon[0].health<<endl;

		cout<<"choose your attack : 1-"<< play1.tabPokemon[0].attackChoice[0].name << endl << "2-" <<play1.tabPokemon[0].attackChoice[1].name <<endl
		<<"3-"<< play1.tabPokemon[0].attackChoice[2].name <<endl<<"4-"<<play1.tabPokemon[0].attackChoice[3].name <<endl;
		cin>>a;

		if(a == 1)
			launchAttack(poke,play1.tabPokemon[0].attackChoice[0]);
		if(a == 2)
			launchAttack(poke,play1.tabPokemon[0].attackChoice[1]);
		if(a == 3)
			launchAttack(poke,play1.tabPokemon[0].attackChoice[2]);
		if(a == 4)
			launchAttack(poke,play1.tabPokemon[0].attackChoice[3]);

		system("clear");
		cout<<"The trainer's pokemon health : "<<poke.health<<endl;
		system("pause");
		cout<<"The Trainer attack you ! Be careful !"<<endl; 
		a= rand() % 3;
		launchAttack(play1.tabPokemon[0],poke.attackChoice[a]);

		cout<<"Your pokemon health : "<<play1.tabPokemon[0].health<<endl;
		system("pause");
	}

 if (play1.tabPokemon[0].health==0)
 {
 	cout<<"You win the fight!! "<<endl
 	play1.addmoney(100);
 	cout<<"Your money : "<<play1.money; 
 	system("pause");
 }
 else {
 	cout << "You loose"; 
 	system("pause");

}
}