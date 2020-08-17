CC=g++
CBFLAGS=-std=c++17 -Wall -fpermissive
CLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lX11 -pthread

OUT=/tmp/a.out

ENGINE=engine/AnimatedTileMap.hpp engine/TileMap.hpp engine/GridMaker.h engine/Node.h engine/UpdateList.h
BASE=$(ENGINE) LogicComponents.h indexes.h textures.h enums.h Entity.h EndScreen.hpp

build: main.o Player.o FullSpawner.o GridMaker.o Node.o UpdateList.o
	$(CC) $(CLFLAGS) -o $(OUT) main.o Player.o FullSpawner.o GridMaker.o Node.o UpdateList.o

main.o: $(BASE) Player.h NodeLoader.hpp
	$(CC) $(CBFLAGS) -o main.o -c main.cpp

Player.o: $(BASE) Player.h
	$(CC) $(CBFLAGS) -o Player.o -c Player.cpp

FullSpawner.o: $(BASE) NodeLoader.hpp Door.hpp AreaSwitch.h Key.hpp Bridge.hpp \
Enemy.h EnemyFireball.h LogicCode.hpp LogicGates.hpp FireLauncher.hpp Helpers.h
	$(CC) $(CBFLAGS) -o FullSpawner.o -c FullSpawner.cpp

GridMaker.o: engine/GridMaker.h
	$(CC) $(CBFLAGS) -o GridMaker.o -c engine/GridMaker.cpp

Node.o: engine/Node.h
	$(CC) $(CBFLAGS) -o Node.o -c engine/Node.cpp

UpdateList.o: engine/UpdateList.h engine/Node.h
	$(CC) $(CBFLAGS) -o UpdateList.o -c engine/UpdateList.cpp

.PHONY: clean run

clean:
	rm -f *.o
