#include "attack.h"
#include "pokemon.h"
#include "battle.cpp"

battle::launchAttack(pokemon pokemon, attack attack)
{
	pokemon.health = pokemon.health-(attack-pokemon.defenseStat);
}

