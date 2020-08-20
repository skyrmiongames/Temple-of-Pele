CC=g++
CBFLAGS=-std=c++17 -Wall -fpermissive
CLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lX11 -pthread

OUT=/tmp/a.out

ENGINE=Skyrmion/AnimatedTileMap.hpp Skyrmion/TileMap.hpp Skyrmion/GridMaker.h Skyrmion/Node.h Skyrmion/UpdateList.h
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

GridMaker.o: Skyrmion/GridMaker.h
	$(CC) $(CBFLAGS) -o GridMaker.o -c Skyrmion/GridMaker.cpp

Node.o: Skyrmion/Node.h
	$(CC) $(CBFLAGS) -o Node.o -c Skyrmion/Node.cpp

UpdateList.o: Skyrmion/UpdateList.h Skyrmion/Node.h
	$(CC) $(CBFLAGS) -o UpdateList.o -c Skyrmion/UpdateList.cpp

.PHONY: clean run

clean:
	rm -f *.o
