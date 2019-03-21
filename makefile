all: bin/pokefac

bin/pokefac: obj/main.o obj/pokemon.o obj/character.o obj/player.o obj/NPC.o obj/terrain.o obj/world.o
	g++ -g -Wall obj/main.o obj/pokemon.o obj/character.o obj/player.o obj/NPC.o obj/terrain.o obj/world.o -o bin/pokefac

obj/main.o: src/main.cpp src/terrain.h src/world.h
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/world.o: src/world.cpp src/world.h src/pokemon.h
	g++ -g -Wall -c src/world.cpp -o obj/world.o

obj/pokemon.o: src/pokemon.cpp src/pokemon.h
	g++ -g -Wall -c src/pokemon.cpp -o obj/pokemon.o

obj/terrain.o: src/terrain.cpp src/terrain.h obj/player.o
	g++ -g -Wall -c src/terrain.cpp -o obj/terrain.o

obj/player.o: src/player.cpp src/player.h
	g++ -g -Wall -c src/player.cpp -o obj/player.o

obj/NPC.o: src/NPC.cpp src/NPC.h
	g++ -g -Wall -c src/NPC.cpp -o obj/NPC.o

obj/character.o: src/character.cpp src/character.h
	g++ -g -Wall -c src/character.cpp -o obj/character.o

clean:
	rm -f obj/*.o
	rm -f bin/*