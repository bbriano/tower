troubledtower: game.o item.o main.o player.o room.o suspect.o utils.o
	clang++ game.o item.o main.o player.o room.o suspect.o utils.o -o tower

game.o: game.h game.cpp
	clang++ -c game.cpp

item.o: item.h item.cpp
	clang++ -c item.cpp

main.o: main.h main.cpp
	clang++ -c main.cpp

player.o: player.h player.cpp
	clang++ -c player.cpp

room.o: room.h room.cpp
	clang++ -c room.cpp

suspect.o: suspect.h suspect.cpp
	clang++ -c suspect.cpp

utils.o: utils.h utils.cpp
	clang++ -c utils.cpp

clean:
	rm *.o
