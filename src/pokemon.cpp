#include "attack.h"
#include "pokemon.h"

pokemon:: launchAttack(pokemon poke,attack att)
{ 

	if( poke.health > 0 && poke.health >= (att.damagePoints - poke.defenseStat))
	poke.health = poke.health - (att.damagePoints-poke.defenseStat);
	else if (poke.health < (att.damagePoints - poke.defenseStat))
		poke.health=0;

}