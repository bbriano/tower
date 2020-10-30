troubledtower: game.o item.o main.o player.o room.o suspect.o utils.o
	g++ game.o item.o main.o player.o room.o suspect.o utils.o -o troubledtower

game.o: game.h game.cpp
	g++ -c game.cpp

item.o: item.h item.cpp
	g++ -c item.cpp

main.o: main.h main.cpp
	g++ -c main.cpp

player.o: player.h player.cpp
	g++ -c player.cpp

room.o: room.h room.cpp
	g++ -c room.cpp

suspect.o: suspect.h suspect.cpp
	g++ -c suspect.cpp

utils.o: utils.h utils.cpp
	g++ -c utils.cpp

clean:
	rm *.o
