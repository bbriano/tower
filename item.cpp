/************************************************************
 *
 * item.cpp
 *
************************************************************/

#include <iostream>
#include "item.h"
#include "utils.h"
#define WINDOW_WIDTH 77  // Not including border

using namespace std;

Item::Item(string name, string imagePath) {
    this->name = name;
    this->image = readFile(imagePath);
}

string Item::getName() {
    return this->name;
}

Room *Item::getRoom() {
    return this->room;
}

void Item::setRoom(Room *room) {
    this->room = room;
}

string Item::getImage() {
    return this->image;
}

// Add blood stains to item image
void Item::addBlood() {
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
