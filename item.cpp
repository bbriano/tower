/************************************************************
 *
 * item.cpp
 *
************************************************************/

#include "item.h"

using namespace std;

Item::Item(string name, string imagePath) {
    this->name = name;
    this->imagePath = imagePath;
}

string Item::getName() {
    return this->name;
}

string Item::getImagePath() {
    return this->imagePath;
}
