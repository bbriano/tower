/************************************************************
 *
 * room.cpp
 *
************************************************************/

#include "room.h"
#include "utils.h"
#define WINDOW_WIDTH 77  // Not including border

using namespace std;

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

// Add blood to room image
void Room::setMurderRoom() {
    string blood = "BLOOD";

    // Replace random column of every other line with "BLOOD"
    for (int i = 1; i <= 32; i++) {
        if (i % 2 == 0) {
            int posible = WINDOW_WIDTH - blood.length() + 1;
            int position = i * 80 + 1 + rand() % posible;
            this->image.replace(position, blood.length(), blood);
        }
    }
}

/****************************** ITEMS ******************************/

vector<Item> Room::getItems() {
    return this->items;
}

void Room::addItem(Item item) {
    this->items.push_back(item);
}

void Room::removeItem(int index) {
    this->items.erase(this->items.begin() + index);
}

// Search for item named itemName in room
// Return index of item if found else return -1
int Room::searchItem(string itemName) {
    int itemIndex = -1;

    for (int i = 0; i < this->items.size(); i++) {
        string roomItemName = this->items[i].getName();
        if (toLower(roomItemName) == toLower(itemName)) {
            itemIndex = i;
        }
    }

    return itemIndex;
}

/****************************** SUSPECTS ******************************/

vector<Suspect*> Room::getSuspects() {
    return this->suspects;
}

// Add a suspect to the suspect list while keeping the sorted order
void Room::addSuspect(Suspect *suspect) {
    // Insert suspect to first position where suspect is smaller than suspects[suspectIndex]
    for (int suspectIndex = 0; suspectIndex < this->suspects.size(); suspectIndex++) {
        if (this->suspects[suspectIndex]->getName() > suspect->getName()) {
            this->suspects.insert(this->suspects.cbegin() + suspectIndex, suspect);
            return;
        }
    }

    // If all elements in suspects is smaller than suspect, push to back
    this->suspects.push_back(suspect);
}

void Room::removeSuspect(int index) {
    this->suspects.erase(this->suspects.begin() + index);
}

// Search for suspect named suspectName in room
// Return index of item if found else return -1
int Room::searchSuspect(string suspectName) {
    int suspectIndex = -1;

    for (int i = 0; i < this->suspects.size(); i++) {
        string roomSuspectName = this->suspects[i]->getName();
        if (toLower(roomSuspectName) == toLower(suspectName)) {
            suspectIndex = i;
            break;
        }
    }

    return suspectIndex;
}

/****************************** NEIGHBOUR ******************************/

void Room::setNeighbour(Direction direction, Room *room) {
    this->neighbour[direction] = room;
}

Room *Room::getNeighbour(Direction direction) {
    return this->neighbour[direction];
}
