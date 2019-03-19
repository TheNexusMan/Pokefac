#include "attack.h"
#include "pokemon.h"

pokemon:: launchAttack(pokemon poke,attack att)
{ 

	if( poke.health > 0 && poke.health >= (att - poke.defenseStat))
	poke.health = poke.health - (att-poke.defenseStat);
	else if (poke.health < (att - poke.defenseStat))
		poke.health=0;

}