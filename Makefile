CXXFLAGS = -std=c++11 -Wall
EXECUTABLE = tower
OBJECTS = game.o item.o main.o player.o room.o suspect.o utils.o

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $(EXECUTABLE) $(OBJECTS)

.o:
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)
