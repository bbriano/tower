/************************************************************
 *
 * game.cpp
 *
 * Implementation of game.h
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>
#include "game.h"
#include "player.h"
#include "item.h"
#include "utils.h"
#define ROOM_ROWS 4
#define ROOM_COLS 3
#define ROOM_WIDTH 25    // Not including border
#define WINDOW_WIDTH 77  // Not including border
#define WINDOW_HEIGHT 39 // Not including border

using namespace std;
string readFile(string fileName);
string readInput(string prompt);

/****************************** PUBLIC METHODS ******************************/

Game::Game(string playerName, Difficulty difficulty) {
    // Create and allocate game objects
    this->createRooms();
    this->createItems();
    this->createSuspects();

    // Create player instance
    Room startingRoom = this->rooms[6];
    this->player = Player(playerName, &startingRoom);
    this->inventory = Room("Inventory");

    // Initialize pointers to NULL
    this->killer = NULL;
    this->victim = NULL;
    this->murderRoom = NULL;
    this->murderWeapon = NULL;

    // Initialize variables
    this->view = VIEW_TOWER;
    this->difficulty = difficulty;
    this->moveCount = 0;
    this->searchCount = 0;
    this->questionCount = 0;
    this->gameOver = false;
    this->gameWin = false;
}

// Display help screen. Wait for user before continuing
void Game::showStoryLine() {
    clearScreen();
    cout << readFile("assets/story_line.txt");
    pause();
}

// Display help screen. Wait for user before continuing
void Game::showHelpScreen() {
    clearScreen();
    cout << readFile("assets/help_screen.txt");
    pause();
}

// Draw image to screen
void Game::displayView() {
    clearScreen();
    switch (this->view) {
        case VIEW_TOWER:
            this->displayTower();
            break;
        case VIEW_ROOM:
            this->displayRoom();
            break;
        case VIEW_INVENTORY:
            this->displayInventory();
            break;
    }
}

// Validate and process user input
void Game::command() {
    // Anatomy of a command:
    //     command    argument (can be multiple words)
    //     \_____/    \______________________________/

    // Read input from user
    string input = toLower(readInput("//> "));
    string command = "";
    string argument = "";
    int spaceIndex = input.find(' ');
    if (spaceIndex == string::npos) {
        command = input.substr(0, spaceIndex);
    } else {
        command = input.substr(0, spaceIndex);
        argument = input.substr(spaceIndex + 1);
    }

    // Game view
    if (command == "view") this->cycleView();
    else if (command == "tower") this->view = VIEW_TOWER;
    else if (command == "room") this->view = VIEW_ROOM;
    else if (command == "inv") this->view = VIEW_INVENTORY;

    // Movement
    else if (command == "left") this->move(DIR_LEFT);
    else if (command == "right") this->move(DIR_RIGHT);
    else if (command == "up") this->move(DIR_UP);
    else if (command == "down") this->move(DIR_DOWN);

    // Item Interactions
    else if (command == "search") this->search();
    else if (command == "pickup") this->pickup(argument);
    else if (command == "drop") this->drop(argument);
    else if (command == "examine") this->examine(argument);

    // Supect Interactions
    else if (command == "question") this->question(argument);
    else if (command == "gather") this->gather();
    else if (command == "accuse") this->accuse(argument);

    else if (command == "stab") this->stab(argument);

    // Utility commands
    else if (command == "help") this->showHelpScreen();
    else if (command == "clear");
    else if (command == "note") this->note(argument);
    else if (command == "easter") cout << "egg\n" << endl, this->command();
    else if (command == "quit") this->confirmQuit();
    else this->invalidCommand();
}

bool Game::getGameWin() {
    return this->gameWin;
}

bool Game::getGameOver() {
    return this->gameOver;
}

/****************************** PRIVATE METHODS ******************************/

// Generate room objects
void Game::createRooms() {
    // Create room instances and append to this->rooms
    this->rooms.push_back(Room("CONTROL CENTER", "assets/room_control_center.txt"));
    this->rooms.push_back(Room("OFFICE",         "assets/room_office.txt"));
    this->rooms.push_back(Room("SPA",            "assets/room_spa.txt"));
    this->rooms.push_back(Room("LABORATORY",     "assets/room_laboratory.txt"));
    this->rooms.push_back(Room("LIBRARY",        "assets/room_library.txt"));
    this->rooms.push_back(Room("GIFT SHOP",      "assets/room_gift_shop.txt"));
    this->rooms.push_back(Room("CAFETARIA",      "assets/room_cafetaria.txt"));
    this->rooms.push_back(Room("LOBBY",          "assets/room_lobby.txt"));
    this->rooms.push_back(Room("TOILET",         "assets/room_toilet.txt"));
    this->rooms.push_back(Room("SERVER ROOM",    "assets/room_server_room.txt"));
    this->rooms.push_back(Room("CAR PARK",       "assets/room_car_park.txt"));
    this->rooms.push_back(Room("PLUMBING ROOM",  "assets/room_plumbing_room.txt"));

    // Set one of the room to be the murder room
    this->murderRoom = &this->rooms[rand() % this->rooms.size()];
    this->murderRoom->addBlood();

    // Set room neighbours. for each room in rooms, set its left, right, up and
    // down neighbouring room if possible (not wall)
    for (int row = 0; row < ROOM_ROWS; row++) {
        for (int col = 0; col < ROOM_COLS; col++) {
            int index = row * ROOM_COLS + col;

            // Set left
            if (col > 0) {
                this->rooms[index].setNeighbour(DIR_LEFT, &this->rooms[index - 1]);
            }

            // Set right
            if (col < ROOM_COLS - 1) {
                this->rooms[index].setNeighbour(DIR_RIGHT, &this->rooms[index + 1]);
            }

            // Set up
            if (row > 0) {
                this->rooms[index].setNeighbour(DIR_UP, &this->rooms[index - ROOM_COLS]);
            }

            // Set down
            if (row < ROOM_ROWS - 1) {
                this->rooms[index].setNeighbour(DIR_DOWN, &this->rooms[index + ROOM_COLS]);
            }
        }
    }
}

// Generate items objects
void Game::createItems() {
    // Create items
    this->items.push_back(Item("Knife", "assets/item_knife.txt"));
    this->items.push_back(Item("Fork", "assets/item_fork.txt"));
    this->items.push_back(Item("Stick", "assets/item_stick.txt"));
    this->items.push_back(Item("Scissors", "assets/item_scissors.txt"));
    this->items.push_back(Item("Bowling ball", "assets/item_bowling_ball.txt"));
    this->items.push_back(Item("Screwdriver", "assets/item_screwdriver.txt"));
    this->items.push_back(Item("Chair", "assets/item_chair.txt"));
    this->items.push_back(Item("Vase", "assets/item_vase.txt"));

    // Set one of the item to be the murder weapon
    this->murderWeapon = &this->items[rand() % this->items.size()];
    this->murderWeapon->addBlood();

    // Put all item in items to a randomly selected room
    for (int i = 0; i < this->items.size(); i++) {
        this->items[i].setLocation(this->getRandomRoom());
    }
}

// Generate suspects objects
void Game::createSuspects() {
    // Create suspects
    this->suspects.push_back(Suspect("Anna"));
    this->suspects.push_back(Suspect("Bob"));
    this->suspects.push_back(Suspect("Charlie"));
    this->suspects.push_back(Suspect("Daniel"));
    this->suspects.push_back(Suspect("Emma"));
    this->suspects.push_back(Suspect("Felix"));
    this->suspects.push_back(Suspect("George"));

    // Put all suspects to a randomly selected room
    for (int i = 0; i < this->suspects.size(); i++) {
        this->suspects[i].setRoom(this->getRandomRoom());
    }

    // Create a vector of pointer to all suspects (for random picking purpose)
    vector<Suspect*> suspectCollection;
    for (int i = 0; i < this->suspects.size(); i++) {
        suspectCollection.push_back(&this->suspects[i]);
    }

    // Shuffle suspect collection
    for (int i = 0; i < suspectCollection.size(); i++) {
        Suspect *temp = suspectCollection[i];
        int randomIndex = rand() % suspectCollection.size();
        suspectCollection[i] = suspectCollection[randomIndex];
        suspectCollection[randomIndex] = temp;
    }

    // Assign victim
    this->victim = suspectCollection.back();
    suspectCollection.pop_back();
    this->victim->setType(SUS_VICTIM);

    // Assign killer
    this->killer = suspectCollection.back();
    suspectCollection.pop_back();
    this->killer->setType(SUS_KILLER);
    this->killer->setAlibi(suspectCollection[rand() % suspectCollection.size()]);

    // Set alibi pairs
    while (suspectCollection.size() > 1) {
        Suspect *suspectA = suspectCollection.back();
        suspectCollection.pop_back();
        Suspect *suspectB = suspectCollection.back();
        suspectCollection.pop_back();

        suspectA->setAlibi(suspectB);
        suspectB->setAlibi(suspectA);
    }
}

// Cycle through all the different views
void Game::cycleView() {
    switch (this->view) {
        case VIEW_TOWER:
            this->view = VIEW_ROOM;
            break;
        case VIEW_ROOM:
            this->view = VIEW_INVENTORY;
            break;
        case VIEW_INVENTORY:
            this->view = VIEW_TOWER;
            break;
    }
}

// Display the tower including the player character where it is located in the tower
void Game::displayTower() {
    // Print tower roof
    cout << "   +-----------------------------------------------------------------------+   " << endl;
    cout << "  /                                                                         \\ " << endl;
    cout << " /                            B R U M P   T O W E R                          \\" << endl;
    cout << "|                                                                             |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;

    // For each floor in the tower
    for (int row = 0; row < ROOM_ROWS; row++) {

        // Status bar on top of each room
        cout << '|';
        for (int col = 0; col < ROOM_COLS; col++) {
            // Display a * for each item in room
            Room *currentRoom = &this->rooms[row * ROOM_COLS + col];
            string itemString = "";
            if (currentRoom->getItemHidden()) {
                itemString = "? ";
            } else {
                for (int i = 0; i < this->items.size(); i++) {
                    if (items[i].getLocation() == currentRoom) {
                        itemString += "* ";
                    }
                }
            }

            // Display the first letter of each suspect in the room
            string suspectString = "";
            for (int i = 0; i < this->suspects.size(); i++) {
                if (this->suspects[i].getRoom() == currentRoom) {
                    suspectString += ' ' + this->suspects[i].getName().substr(0, 1);
                }
            }

            // Example display format: | A B C D E F G * * * * * |
            int blankCount = ROOM_WIDTH - itemString.length() - suspectString.length();
            cout << fixedWidth(suspectString + fixedWidth("", ' ', blankCount) + itemString, ' ', ROOM_WIDTH) << '|';
        }
        cout << '\n';

        // Display the main section of the room (where the character might be)
        for (int i = 0; i < 6; i++) {
            cout << '|';
            for (int col = 0; col < ROOM_COLS; col++) {
                string content = "";

                Room *currentRoom = &this->rooms[row * ROOM_COLS + col];
                if (currentRoom == this->player.getRoom()) {
                    content = this->player.getImage()[i];
                }

                cout << fixedWidth(content, ' ', ROOM_WIDTH) << '|';
            }
            cout << '\n';
        }

        // Print names of rooms in the current floor
        cout << '|';
        for (int col = 0; col < ROOM_COLS; col++) {
            string roomName = this->rooms[row * ROOM_COLS + col].getName();
            cout << fixedWidth(" " + roomName, ' ', ROOM_WIDTH) << '|';
        }
        cout << '\n';

        cout << "+-----------------------------------------------------------------------------+" << endl;
    }
}

// Display the room where the player is in
void Game::displayRoom() {
    Room *currentRoom = this->player.getRoom();

    // Display the current room's image and description
    cout << currentRoom->getImage();
    cout << "|                                                                             |" << endl;

    // Display each item that exists in the current room
    string itemsString = "  ITEMS: ";
    if (currentRoom->getItemHidden()) {
        itemsString += '?';
    } else {
        vector<Item *> items;
        for (int i = 0; i < this->items.size(); i++) {
            if (this->items[i].getLocation() == currentRoom) {
                items.push_back(&this->items[i]);
            }
        }
        if (items.size() > 0) {
            itemsString += items[0]->getName();
            for (int i = 1; i < items.size(); i++) {
                itemsString += ", " + items[i]->getName();
            }
        } else {
            itemsString += '-';
        }
    }
    cout << '|' << fixedWidth(itemsString, ' ', WINDOW_WIDTH) << '|' << endl;
    cout << "|                                                                             |" << endl;

    // Display all suspect in the current room
    string suspectsString = "  SUSPECTS: ";
    vector<Suspect *> suspects;
    for (int i = 0; i < this->suspects.size(); i++) {
        if (this->suspects[i].getRoom() == currentRoom) {
            suspects.push_back(&this->suspects[i]);
        }
    }
    if (suspects.size() > 0) {
        suspectsString += suspects[0]->getName();
        for (int i = 1; i < suspects.size(); i++) {
            suspectsString += ", " + suspects[i]->getName();
        }
    } else {
        suspectsString += '-';
    }
    cout << '|' << fixedWidth(suspectsString, ' ', WINDOW_WIDTH) << '|' << endl;
    cout << "|                                                                             |" << endl;

    cout << "+-----------------------------------------------------------------------------+" << endl;
}

// Display player's inventory full screen
void Game::displayInventory() {
    cout << "+-----------------------------------------------------------------------------+" << endl;

    // Print title
    cout << '|' << fixedWidth("", ' ', WINDOW_WIDTH) << '|' << endl;
    cout << '|' << fixedWidth("  INVENTORY", ' ', WINDOW_WIDTH) << '|' << endl;

    // Print items in player's inventory
    for (int i = 0; i < this->getInventory().size(); i++) {
        cout << '|' << fixedWidth("", ' ', WINDOW_WIDTH) << '|' << endl;
        cout << '|' << fixedWidth("  - " + this->getInventory()[i]->getName(), ' ', WINDOW_WIDTH) << '|' << endl;
    }

    // Print blank lines
    for (int i = 0; i < WINDOW_HEIGHT - this->getInventory().size() * 2 - 2; i++) {
        if (i == 1 && this->getInventory().size() == 0) {
            // Print empty. if nothing in inventory
            cout << '|' << fixedWidth("  Empty.", ' ', WINDOW_WIDTH) << '|' << endl;
        } else {
            cout << '|' << fixedWidth("", ' ', WINDOW_WIDTH) << '|' << endl;
        }
    }

    cout << "+-----------------------------------------------------------------------------+" << endl;
}

// Get confirmation from user if they want to quit
void Game::confirmQuit() {
    string answer = readInput("Are you sure? (Y/n) ");
    if (answer == "y" || answer == "Y") {
        this->gameOver = true;
    }
}

// If the user puts an invalid command suggest them to read the help screen
void Game::invalidCommand() {
    cout << "Get some '//> help'\n" << endl;
    this->command();  // Prompt for command again. No re-render
}

// Display a response from the suspect named suspectName
void Game::question(string suspectName) {
    Suspect *suspect = this->searchSuspect(suspectName);

    // Suspect can only talk if in the same room as player
    if (suspect && suspect->getRoom() == this->player.getRoom()) {
        suspect->talk(this->player.getName());
    } else {
        cout << "'" << suspectName << "' not found in room" << endl;
    }

    this->questionCount++;

    // If questioned more than 3 times in nightmare mode, end the game
    if (this->questionCount > 3) {
        cout << "Shhhh....\n" << endl;
        pause();
        this->gameOver = true;
    } else {
        this->command();
    }
}

// Move all suspect to the room where the player is in
void Game::gather() {
    for (int i = 0; i < this->suspects.size(); i++) {
        if (&this->suspects[i] != this->victim) {
            this->suspects[i].setRoom(this->player.getRoom());
        }
    }
}

// Return a pointer to a random room
Room *Game::getRandomRoom() {
    return &this->rooms[rand() % this->rooms.size()];
}

// Return a pointer to the room named roomName and return NULL if not found
Room *Game::searchRoom(std::string roomName) {
    for (int i = 0; i < this->rooms.size(); i++) {
        if (toLower(this->rooms[i].getName()) == toLower(roomName)) {
            return &this->rooms[i];
        }
    }

    return NULL;
}

// Return a pointer to the suspect named suspectName and return NULL if not found
Suspect *Game::searchSuspect(string suspectName) {
    for (int i = 0; i < this->suspects.size(); i++) {
        if (toLower(this->suspects[i].getName()) == toLower(suspectName)) {
            return &this->suspects[i];
        }
    }

    return NULL;
}

// Return a pointer to an item named itemName and return NULL if not found
Item *Game::searchItem(string itemName) {
    for (int i = 0; i < this->items.size(); i++) {
        if (toLower(this->items[i].getName()) == toLower(itemName)) {
            return &this->items[i];
        }
    }

    return NULL;
}

// Search for item in room add to inventory if found
void Game::pickup(string itemName) {
    Item *item = this->searchItem(itemName);

    if (item && item->getLocation() == this->player.getRoom()) {
        item->setLocation(&this->inventory);
    } else {
        this->command();
    }

    // If easy mode, picking up all items in the tower results in a win
    if (this->difficulty == DIFF_EASY && this->getInventory().size() == this->items.size()) {
        this->gameWin = true;
        this->gameOver = true;
    }
}

// Drop item named itemName to player's room if found in inventory
void Game::drop(string itemName) {
    Item *item = this->searchItem(itemName);

    if (item && item->getLocation() == &this->inventory) {
        item->setLocation(this->player.getRoom());
    } else {
        this->command();
    }
}

// Display item named itemName in player's inventory if exists
void Game::examine(string itemName) {
    Item *item = this->searchItem(itemName);

    if (item && item->getLocation() == &this->inventory) {
        clearScreen();
        cout << item->getImage();
        cout << "|                                                                             |" << endl;
        cout << '|' << fixedWidth("  ITEM NAME: " + item->getName(), ' ', WINDOW_WIDTH) << '|' << endl;
        cout << "|                                                                             |" << endl;
        cout << '|' << fixedWidth("  LOCATION: " + item->getLocation()->getName(), ' ', WINDOW_WIDTH) << '|' << endl;
        cout << "|                                                                             |" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
        pause();
    } else {
        this->command();
    }
}

void Game::accuse(string suspectName) {
    if (this->difficulty == DIFF_NIGHTMARE) {
        cout << "Sorry, accusing is not an option in nightmare mode\n" << endl;
        return;
    }

    Suspect *suspect = this->searchSuspect(suspectName);
    if (suspect) {
        if (suspect == this->killer) {
            string roomName = readInput("Where did the murder took place? ");
            cout << endl;
            Room *room = this->searchRoom(roomName);
            if (room) {
                if (room == this->murderRoom) {
                    string itemName = readInput("What weapon did the murderer used? ");
                    cout << endl;
                    Item *weapon = searchItem(itemName);
                    if (weapon) {
                        if (weapon == this->murderWeapon) {
                            this->gameWin = true;
                            this->gameOver = true;
                        } else {
                            cout << "Wrong.\n" << endl;
                            pause();
                            this->gameOver = true;
                        }
                    } else {
                        cout << "item named '" << itemName << "' not found\n" << endl;
                        this->command();
                    }
                } else {
                    cout << "Wrong.\n" << endl;
                    pause();
                    this->gameOver = true;
                }
            } else {
                cout << "room named '" << roomName << "' not found\n" << endl;
                this->command();
            }
        } else {
            cout << "Wrong.\n" << endl;
            pause();
            this->gameOver = true;
        }
    } else {
        cout << "suspect named '" << suspectName << "' not found\n" << endl;
        this->command();
    }
}

// Return a list of item pointer of items in inventory
vector<Item *> Game::getInventory() {
    vector<Item *> inventoryItems;

    for (int i = 0; i < this->items.size(); i++) {
        if (items[i].getLocation() == &this->inventory) {
            inventoryItems.push_back(&items[i]);
        }
    }

    return inventoryItems;
}

// Move to room besides current player room if it exists
void Game::move(Direction direction) {
    // Move the player
    Room *destination = this->player.getRoom()->getNeighbour(direction);
    if (destination != NULL) {
        this->player.setRoom(destination);
        this->moveCount++;
    }

    // Randomly move the suspects
    for (int i = 0; i < this->suspects.size(); i++) {
        Direction randomDirection = static_cast<Direction>(rand() % 4);
        this->suspects[i].move(randomDirection);
    }

    // If move more than 10 times in hard mode, end the game
    if (this->difficulty == DIFF_HARD && this->moveCount > 10) {
        cout << "Hippity hoppity.. too much movement, your leg break\n" << endl;
        pause();
        this->gameOver = true;
    }
}

// Search the current room the player is in
void Game::search() {
    this->player.getRoom()->search();
    this->searchCount++;

    // If searched more than 3 rooms in nightmare mode, end the game
    if (this->difficulty == DIFF_NIGHTMARE && this->searchCount > 3) {
        cout << "Don't search too much or you will be one getting searched >:D\n" << endl;
        pause();
        this->gameOver = true;
    }
}

// Stab a suspect for the nightmare mode
void Game::stab(string suspectName) {
    // Check if game is in nightmare difficulty and exit function if not
    if (this->difficulty != DIFF_NIGHTMARE) {
        cout << "Stabbing only in nightmare mode.\n" << endl;
        this->command();
        return;
    }

    // Check if player have the knife
    Item *foundKnife = this->searchItem("knife");
    if (!foundKnife) {
        cout << "You don't have a knife...\n" << endl;
        return;
    }

    // Win if stabbed the killer, else end the game with a loss
    Suspect *suspect = this->searchSuspect(suspectName);
    if (suspect && suspect->getRoom() == this->player.getRoom()) {
        if (suspect == this->killer) {
            this->gameWin = true;
        } else {
            cout << "Congratulation on stabbing an innocent person..\n" << endl;
            pause();
        }
        this->gameOver = true;
    } else {
        cout << "Suspect named '" << suspectName << "' not found in this room\n" << endl;
    }
}

// Display notes if content is empty else add content to notes
void Game::note(string content) {
    if (content != "") {
        // Append content to notes
        this->notes.push_back(content);
    } else {
        // Display notes
        clearScreen();
        cout << "+-----------------------------------------------------------------------------+" << endl;

        // Print each line in notes
        for (int i = 0; i < this->notes.size(); i++) {
            cout << "|                                                                             |" << endl;
            cout << "|  " << fixedWidth(this->notes[i], ' ', WINDOW_WIDTH - 4) << "  |" << endl;
        }

        // Print blank lines to fill the screen
        int blankCount = WINDOW_HEIGHT - 2 * this->notes.size();
        for (int i = 0; i < blankCount; i++) {
            cout << "|                                                                             |" << endl;
        }

        cout << "+-----------------------------------------------------------------------------+" << endl;
        pause();
    }
}
