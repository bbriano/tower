/************************************************************
 *
 * suspect.cpp
 *
************************************************************/

#include <iostream>
#include "suspect.h"
#include "utils.h"

using namespace std;

// Suspect constructor
Suspect::Suspect(string name) {
    this->name = name;
    this->type = SUS_NORMAL;
    this->alibi = NULL;
}

// Return the name of the suspect
string Suspect::getName() {
    return this->name;
}

Room *Suspect::getRoom() {
    return this->room;
}

// Set the location of the suspect
void Suspect::setRoom(Room *room) {
    this->room = room;
}

// Mutator method to set the type of the suspect
void Suspect::setType(SuspectType type) {
    this->type = type;
}

// Set the alibi of the suspect
void Suspect::setAlibi(Suspect *alibi) {
    this->alibi = alibi;
}

// Display messages from the suspect
void Suspect::talk(string playerName) {
    switch (this->type) {
        case SUS_NORMAL:
        case SUS_KILLER:
            cout << "Hi " << playerName << ", ";

            if (this->alibi == NULL) {
                cout << "I was alone";
            } else {
                cout << "I was with " << this->alibi->getName();
            }

            break;
        case SUS_VICTIM:
            cout << "X_X";
            break;
    }
    cout << '\n' << endl;
}

// Move to neighbouring room based on given direction
void Suspect::move(Direction direction) {
    Room *destination = this->room->getNeighbour(direction);
    // Move to destination if it exists
    if (destination) this->room = destination;
}
