/************************************************************
 *
 * room.cpp
 *
 * Represents the room object
 * Player, item and suspect all points to a room
 * Can access neighbouring rooms in all 4 directions
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#include "room.h"
#include "utils.h"
#define WINDOW_WIDTH 77  // Not including border

using namespace std;

// Default constructor so can be invoked from game
Room::Room() { }

// Initialize room name and load image from file
Room::Room(string name, string imagePath) {
    // Initialize class variables
    this->name = name;
    this->image = readFile(imagePath);
    this->itemHidden = true;
    this->murderRoom = false;

    // Initialize neighbours to NULL
    this->neighbour[DIR_LEFT] = NULL;
    this->neighbour[DIR_RIGHT] = NULL;
    this->neighbour[DIR_UP] = NULL;
    this->neighbour[DIR_DOWN] = NULL;
}

// Return the room name
string Room::getName() {
    return this->name;
}

// Return the room image as a ascii art string
string Room::getImage() {
    return this->image;
}

// Return true if room have not been search
bool Room::getItemHidden() {
    return this->itemHidden;
}

// Set item to not hidden if room is searched
void Room::search() {
    this->itemHidden = false;
}

// Return true if room is the murder room else false
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

// Set neighbour room in direction
void Room::setNeighbour(Direction direction, Room *room) {
    this->neighbour[direction] = room;
}

// Get neighbouring room provided a direction
Room *Room::getNeighbour(Direction direction) {
    return this->neighbour[direction];
}
