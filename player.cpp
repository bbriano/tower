#include <iostream>
#include <string>
#include "player.h"
#include "room.h"
#include "utils.h"

using namespace std;

Player::Player() {
    this->name = "John";
}

Player::Player(string name, Room *startingRoom) {
    this->name = name;
    this->room = startingRoom;

    this->image.push_back("           ___");
    this->image.push_back("          /@ @\\");
    this->image.push_back("          \\___/");
    this->image.push_back("          __|__");
    this->image.push_back("            |");
    this->image.push_back("           / \\");
}

string Player::getName() {
    return this->name;
}

vector<string> Player::getImage() {
    return this->image;
}

Room *Player::getRoom() {
    return this->room;
}

void Player::move(Direction direction) {
    Room *destination = this->room->getNeighbour(direction);
    if (destination != NULL) {
        this->room = destination;
    }
}

/****************************** ITEM INTERACTIONS ******************************/

// Get all items in player's inventory
vector<Item> Player::getInventory() {
    return this->inventory;
}

// Search for item in player's current room. Move item to player's inventory if found
void Player::pickupItem(string itemName) {
    int itemIndex = this->room->searchItem(itemName);

    // Move item from current room to inventory if found
    if (itemIndex >= 0) {
        this->inventory.push_back(this->room->getItems()[itemIndex]);
        this->room->removeItem(itemIndex);
    }
}

// Search for item in player's inventory. Move item to player's current room if found
void Player::dropItem(string itemName) {
    int itemIndex = this->searchInventory(itemName);

    // Move item from inventory to current room if found
    if (itemIndex >= 0) {
        this->room->addItem(this->inventory[itemIndex]);
        this->inventory.erase(this->inventory.begin() + itemIndex);
    }
}

// Search and display item
void Player::inspectItem(string itemName) {
    int itemIndex = this->searchInventory(itemName);

    // Display item if found
    if (itemIndex >= 0) {
        this->inventory[itemIndex].display();
    }
}

// Search for item named itemName in player's inventory
// Return index of item if found else return -1
int Player::searchInventory(string itemName) {
    int itemIndex = -1;

    for (int i = 0; i < this->inventory.size(); i++) {
        string invItemName = this->inventory[i].getName();
        if (toLower(invItemName) == toLower(itemName)) {
            itemIndex = i;
        }
    }

    return itemIndex;
}
