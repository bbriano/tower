#include <iostream>
#include <string>
#include "player.h"
#include "room.h"
#include "utils.h"

using namespace std;

Player::Player() {
    this->name = "";
}

Player::Player(string name, Room *startingRoom) {
    this->name = name;

    this->image.push_back("           ___");
    this->image.push_back("          /@ @\\");
    this->image.push_back("          \\___/");
    this->image.push_back("          __|__");
    this->image.push_back("            |");
    this->image.push_back("           / \\");

    this->room = startingRoom;
    this->room = this->room->getNeighbour(DIR_RIGHT);
}

string Player::getName() {
    return this->name;
}

vector<string> Player::getImage() {
    return this->image;
}

void Player::setRoom(Room *room) {
    this->room = room;
}

Room *Player::getRoom() {
    return this->room;
}
