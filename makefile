INCLUDE_SDL= -I/usr/include/SDL2
LIBS_SDL=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


all: bin/pokefac bin/pokefacSDL

bin/pokefac: obj/main.o obj/pokemon.o obj/character.o obj/player.o obj/NPC.o obj/terrain.o obj/world.o obj/loopTxT.o obj/winTxt.o 
	g++ -g -Wall obj/main.o obj/pokemon.o obj/character.o obj/player.o obj/NPC.o obj/terrain.o obj/world.o obj/loopTxT.o obj/winTxt.o -o bin/pokefac 

bin/pokefacSDL: obj/mainSDL.o obj/pokemon.o obj/character.o obj/player.o obj/NPC.o obj/terrain.o obj/world.o obj/loopTxT.o obj/winTxt.o obj/sdlGameLoop.o
	g++ -g -Wall obj/mainSDL.o obj/pokemon.o obj/character.o obj/player.o obj/NPC.o obj/terrain.o obj/world.o obj/loopTxT.o obj/winTxt.o obj/sdlGameLoop.o -o bin/pokefacSDL $(LIBS_SDL)

obj/mainSDL.o: src/main.cpp src/terrain.h src/world.h
	g++ -g -Wall -c src/mainSDL.cpp -o obj/mainSDL.o $(LIBS_SDL) $(INCLUDE_SDL)

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

obj/loopTxT.o: src/loopTxT.cpp src/loopTxT.h
	g++ -g -Wall -c src/loopTxT.cpp -o obj/loopTxT.o

obj/winTxt.o: src/winTxt.cpp src/winTxt.h
	g++ -g -Wall -c src/winTxt.cpp -o obj/winTxt.o

obj/sdlGameLoop.o: src/sdlGameLoop.cpp src/sdlGameLoop.h
	g++ -g -Wall -c src/sdlGameLoop.cpp -o obj/sdlGameLoop.o $(INCLUDE_SDL) -Isrc/



clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -r data/logs

veryclean: clean
	rm -r data/saveGames
