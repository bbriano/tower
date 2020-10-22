/************************************************************
 *
 * game.cpp
 *
 * Implementation of game.h
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

// NOTE: Can add upto 19 items before screen overflow in room display
// NOTE: Game mode idea: pickup all the items as fast as possible (maybe this could be easy mode)
//
// Easy      -> pickup all items as fast as possible. No time limit
// Medium    ->
// Medium    ->
// Nightmare ->

#include <iostream>
#include <sstream>
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
    cout << this->player.getRoom()->getName() << endl;
    this->player.move(DIR_RIGHT);  // NOTE: For some reason have to put line below else player dont show first time in tower

    // Initialize variables
    this->gameOver = false;
    this->foundKiller = false;
    this->view = VIEW_TOWER;
    this->difficulty = difficulty;
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
    //     command    argument can be multiple words
    //     \_____/    \____________________________/

    int index;
    string command = "";
    string argument = "";

    // Read input from user
    string input = toLower(readInput("//> "));
    if ((index = input.find(' ')) == string::npos) {
        // Command only
        command = input.substr(0, index);
    } else {
        // Command with arguments
        command = input.substr(0, index);
        argument = input.substr(index + 1);
    }

    // Game view
    if (command == "view") this->cycleView();
    else if (command == "tower") this->view = VIEW_TOWER;
    else if (command == "room") this->view = VIEW_ROOM;
    else if (command == "inv") this->view = VIEW_INVENTORY;

    // Movement
    else if (command == "left") this->player.move(DIR_LEFT);
    else if (command == "right") this->player.move(DIR_RIGHT);
    else if (command == "up") this->player.move(DIR_UP);
    else if (command == "down") this->player.move(DIR_DOWN);

    // Interaction
    else if (command == "pickup") this->player.pickupItem(argument);
    else if (command == "drop") this->player.dropItem(argument);

    // Easter season
    else if (command == "easter") cout << "egg" << endl;

    // Utility commands
    else if (command == "help") this->showHelpScreen();
    else if (command == "quit") this->confirmQuit();
    else this->invalidCommand();
}

bool Game::getFoundKiller() {
    return this->foundKiller;
}

bool Game::getGameOver() {
    return this->gameOver;
}

/****************************** PRIVATE METHODS ******************************/

// Generate room objects and link them all together
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

// Generate items and allocate each item to a random room
void Game::createItems() {
    // Create items
    vector<Item> items;
    items.push_back(Item("Knife", "assets/item_knife.txt"));
    items.push_back(Item("Fork", "assets/item_fork.txt"));
    items.push_back(Item("Stick", "assets/item_fork.txt"));
    items.push_back(Item("Scissor", "assets/item_fork.txt"));
    items.push_back(Item("Ball", "assets/item_fork.txt"));
    items.push_back(Item("Screwdriver", "assets/item_fork.txt"));
    items.push_back(Item("Light bulb", "assets/item_fork.txt"));
    items.push_back(Item("Vase", "assets/item_fork.txt"));

    // Put all item in items to a randomly selected room
    for (int i = 0; i < items.size(); i++) {
        Room *randomRoom = &this->rooms[rand() % this->rooms.size()];
        randomRoom->addItem(items[i]);
    }
}

void Game::createSuspects() {
    // TODO
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

        // Display a * for each item in room
        cout << '|';
        for (int col = 0; col < ROOM_COLS; col++) {
            int itemCount = this->rooms[row * ROOM_COLS + col].getItems().size();
            string stars = "";
            for (int i = 0; i < itemCount; i++) {
                stars += " *";
            }
            cout << fixedWidth(stars, ' ', ROOM_WIDTH) << '|';
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
    cout << readFile(currentRoom->getImagePath());

    // Display each item that exists in the current room
    if (currentRoom->getItems().size() > 0) {
        cout << "Items: " << currentRoom->getItems()[0].getName();
        for (int i = 1; i < currentRoom->getItems().size(); i++) {
            cout << ", " << currentRoom->getItems()[i].getName();
        }
        cout << endl;
    }
}

// Display player's inventory full screen
void Game::displayInventory() {
    cout << "+-----------------------------------------------------------------------------+" << endl;

    vector<Item> inventory = this->player.getInventory();

    // Print items in player's inventory
    for (int i = 0; i < inventory.size(); i++) {
        cout << '|' << fixedWidth("", ' ', WINDOW_WIDTH) << '|' << endl;
        cout << '|' << fixedWidth(" " + inventory[i].getName(), ' ', WINDOW_WIDTH) << '|' << endl;
    }

    // Print blank lines
    for (int i = 0; i < WINDOW_HEIGHT - this->player.getInventory().size() * 2; i++) {
        cout << '|' << fixedWidth("", ' ', WINDOW_WIDTH) << '|' << endl;
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

void Game::invalidCommand() {
    cout << "Get some '//> help'\n" << endl;
    this->command();  // Prompt for command again. No re-render
}
