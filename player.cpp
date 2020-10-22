#include <iostream>
#include <string>
#include "player.h"
#include "room.h"
#include "utils.h"

using namespace std;

// TODO: Ask tutor why this default constructor must exists
Player::Player() { }

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

vector<Item> Player::getInventory() {
    return this->inventory;
}

void Player::move(Direction direction) {
    Room *destination = this->room->getNeighbour(direction);
    if (destination != NULL) {
        this->room = destination;
    }
}

// Search for item in player's current room. Move item to player's inventory if found
void Player::pickupItem(string itemName) {
    int itemIndex = -1;

    for (int i = 0; i < this->room->getItems().size(); i++) {
        string roomItemName = this->room->getItems()[i].getName();
        if (toLower(roomItemName) == toLower(itemName)) {
            itemIndex = i;
        }
    }

    // Move item from current room to inventory if found
    if (itemIndex == -1) {
        cout << "Item '" << itemName << "' not in room" << endl;
        pause();
    } else {
        this->inventory.push_back(this->room->getItems()[itemIndex]);
        this->room->removeItem(itemIndex);
    }
}

// Search for item in player's inventory. Move item to player's current room if found
void Player::dropItem(string itemName) {
    int itemIndex = -1;

    for (int i = 0; i < this->inventory.size(); i++) {
        string invItemName = this->inventory[i].getName();
        if (toLower(invItemName) == toLower(itemName)) {
            itemIndex = i;
        }
    }

    // Move item from inventory to current room if found
    if (itemIndex == -1) {
        cout << "Item '" << itemName << "' not in inventory" << endl;
        pause();
    } else {
        this->room->addItem(this->inventory[itemIndex]);
        this->inventory.erase(this->inventory.begin() + itemIndex);
    }
}
