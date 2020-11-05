/************************************************************
 *
 * item.cpp
 *
 * Represents an item object
 * Might be the murder weapon
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#include <iostream>
#include "item.h"
#include "utils.h"
#define WINDOW_WIDTH 77  // Not including border

using namespace std;

// Initialize class variables
Item::Item(string name, string imagePath) {
    this->name = name;
    this->image = readFile(imagePath);
    this->murderWeapon = false;
}

// Return the name of the item
string Item::getName() {
    return this->name;
}

// Return a pointer to the location of the item
Room *Item::getLocation() {
    return this->location;
}

// Set the location of the item
void Item::setLocation(Room *room) {
    this->location = room;
}

// Return the item image as an ascii art string
string Item::getImage() {
    return this->image;
}

// Return true if item is the murder weapon else false
bool Item::getMurderWeapon() {
    return this->murderWeapon;
}

// Set murder room and add blood stains to item image
void Item::setMurderWeapon() {
    this->murderWeapon = true;

    // Replace random column of every other line with "BLOOD"
    string blood = "BLOOD";
    for (int i = 1; i <= 34; i++) {
        if (i % 2 == 0) {
            int posible = WINDOW_WIDTH - blood.length() + 1;
            int position = i * 80 + 1 + rand() % posible;
            this->image.replace(position, blood.length(), blood);
        }
    }
}
