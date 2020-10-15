#include "player.h"
#include "room.h"
#include <string>

using namespace std;

Player::Player() {
}

Player::Player(string name, Room *startingRoom) {
    this->name = name;
    this->room = startingRoom;
}

string Player::getName() {
    return this->name;
}

vector<Item> Player::getInventory() {
    return this->inventory;
}
