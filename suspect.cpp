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
Suspect::Suspect(string name, string imagePath) {
    this->name = name;
    this->imagePath = imagePath;
    this->type = SUS_NORMAL;
    this->alibi = NULL;
}

// Return the name of the suspect
string Suspect::getName() {
    return this->name;
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
            cout << "Hi " << playerName << ", my name is " << this->name << endl;

            if (this->alibi == NULL) {
                cout << "I was alone" << endl;
            } else {
                cout << "I was with " << this->alibi->getName() << endl;
            }

            break;
        case SUS_KILLER:
            cout << "I am kille" << endl;
            break;
        case SUS_VICTIM:
            cout << "X_X";
            break;
    }
    cout << '\n' << endl;
}
