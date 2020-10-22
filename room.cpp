/************************************************************
 *
 * room.cpp
 *
************************************************************/

#include "room.h"

using namespace std;

Room::Room(string name, string imagePath) {
    this->name = name;
    this->imagePath = imagePath;

    // Initialize neighbours to NULL
    this->neighbour[DIR_LEFT] = NULL;
    this->neighbour[DIR_RIGHT] = NULL;
    this->neighbour[DIR_UP] = NULL;
    this->neighbour[DIR_DOWN] = NULL;
}

string Room::getName() {
    return this->name;
}

string Room::getImagePath() {
    return this->imagePath;
}

vector<Item> Room::getItems() {
    return this->items;
}

void Room::addItem(Item item) {
    this->items.push_back(item);
}

void Room::removeItem(int index) {
    this->items.erase(this->items.begin() + index);
}

void Room::setNeighbour(Direction direction, Room *room) {
    this->neighbour[direction] = room;
}

Room *Room::getNeighbour(Direction direction) {
    return this->neighbour[direction];
}
