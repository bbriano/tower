/************************************************************
 *
 * item.cpp
 *
************************************************************/

#include <iostream>
#include "item.h"
#include "utils.h"

using namespace std;

Item::Item(string name, string imagePath) {
    this->name = name;
    this->imagePath = imagePath;
}

string Item::getName() {
    return this->name;
}

// Display the item, load from file
void Item::display() {
    clearScreen();
    cout << readFile(this->imagePath);
    pause();
}
