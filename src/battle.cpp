#include "attack.h"
#include "pokemon.h"
#include "battle.cpp"

battle::launchAttack(pokemon pokemon, attack attack)
{
	if( pokemon.health > 0 && pokemon.health >= (attack - pokemon.defenseStat))
	pokemon.health = pokemon.health - (attack-pokemon.defenseStat);
	else if (pokemon.health < (attack - pokemon.defenseStat))
		pokemon.health=0;
}

launchBattle(player play1, pokemon poke)
{
	while(play1.tabPokemon[0].health > 0 || poke.health > 0)
	{
		cout<<"choose your attack : 1-Attaque éclaire (-10) "
	}
	
}