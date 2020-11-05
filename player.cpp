/************************************************************
 *
 * player.cpp
 *
 * Represents the player in the game
 * Stores player's name, location and image
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#include <iostream>
#include "player.h"
#include "room.h"
#include "utils.h"

using namespace std;

// Default constructor, initialize name and room to NULL
Player::Player() {
    this->name = "";
    this->room = NULL;
}

// Initialize player variable and set player image
Player::Player(string name, Room *startingRoom) {
    this->name = name;
    this->room = startingRoom->getNeighbour(DIR_RIGHT);

    // Load the image of the player from file
    image = stringSplit(readFile("assets/player.txt"), '\n');
}

// Return the player's name
string Player::getName() {
    return this->name;
}

// Return the player's image string vector
vector<string> Player::getImage() {
    return this->image;
}

// Set the player's location
void Player::setRoom(Room *room) {
    this->room = room;
}

// Get player's location as a pointer to a room
Room *Player::getRoom() {
    return this->room;
}
