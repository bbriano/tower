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
