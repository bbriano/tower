#include "room.h"

using namespace std;

Room::Room(string name, string description, string image) {
    this->name = name;
    this->description = description;
    this->image = image;

    // Initialize neighbours to NULL
    this->neighbour[DIR_LEFT] = NULL;
    this->neighbour[DIR_RIGHT] = NULL;
    this->neighbour[DIR_UP] = NULL;
    this->neighbour[DIR_DOWN] = NULL;
}

string Room::getName() {
    return this->name;
}

void Room::setNeighbour(Direction direction, Room *room) {
    this->neighbour[direction] = room;
}

Room *Room::getNeighbour(Direction direction) {
    return this->neighbour[direction];
}
