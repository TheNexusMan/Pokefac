all: bin/pokefac

bin/pokefac: obj/main.o obj/terrain.o obj/world.o
	g++ -g -Wall obj/main.o obj/terrain.o -o bin/pokefac

obj/main.o: src/main.cpp src/terrain.h src/world.h
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/world.o: src/world.cpp src/world.h
	g++ -g -Wall -c src/world.cpp -o obj/world.o

obj/terrain.o: src/terrain.cpp src/terrain.h
	g++ -g -Wall -c src/terrain.cpp -o obj/terrain.o

clean:
	rm -f obj/*.o
	rm -f bin/*