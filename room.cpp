/************************************************************
 *
 * room.cpp
 *
************************************************************/

#include "room.h"
#include "utils.h"
#define WINDOW_WIDTH 77  // Not including border

using namespace std;

Room::Room() { }

Room::Room(string name) {
    this->name = name;
}

Room::Room(string name, string imagePath) {
    // Initialize class variables
    this->name = name;
    this->image = readFile(imagePath);
    this->itemHidden = true;
    /* this->isMurderRoom = false; */

    // Initialize neighbours to NULL
    this->neighbour[DIR_LEFT] = NULL;
    this->neighbour[DIR_RIGHT] = NULL;
    this->neighbour[DIR_UP] = NULL;
    this->neighbour[DIR_DOWN] = NULL;
}

string Room::getName() {
    return this->name;
}

string Room::getImage() {
    return this->image;
}

bool Room::getItemHidden() {
    return this->itemHidden;
}

void Room::search() {
    this->itemHidden = false;
}

bool Room::getMurderRoom() {
    return this->murderRoom;
}

// Set murder room and add blood to room
void Room::setMurderRoom() {
    this->murderRoom = true;

    // Replace random column of every other line with "BLOOD"
    string blood = "BLOOD";
    for (int i = 1; i <= 33; i++) {
        if (i % 2 == 0) {
            int posible = WINDOW_WIDTH - blood.length() + 1;
            int position = i * 80 + 1 + rand() % posible;
            this->image.replace(position, blood.length(), blood);
        }
    }
}

void Room::setNeighbour(Direction direction, Room *room) {
    this->neighbour[direction] = room;
}

Room *Room::getNeighbour(Direction direction) {
    return this->neighbour[direction];
}
