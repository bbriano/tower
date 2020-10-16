#define ROOM_ROWS 4
#define ROOM_COLS 3
#include <iostream>
#include "game.h"
#include "player.h"
#include "utils.h"

using namespace std;
string readFile(string fileName);
string readInput(string prompt);

Game::Game(string playerName) {
    // Create and allocate rooms
    this->createRooms();

    // Create player instance
    Room startingRoom = this->rooms[0];
    this->player = Player(playerName, &startingRoom);
    cout << this->player.getRoom()->getName() << endl;

    // Initialize variables
    this->gameOver = false;
    this->gameOver = false;
    this->view = VIEW_TOWER;

    // Show story line and help screen before running the main game loop
    this->showStoryLine();
    this->showHelpScreen();
    this->runGameLoop();
}

// Render view. Read command. Repeat.
// Return true if the killer is found (player won), and false otherwise
void Game::runGameLoop() {
    while (!gameOver) {
        this->renderView();
        this->command();
    }
}

// Draw image to screen
void Game::renderView() {
    clearScreen();
    switch (this->view) {
        case VIEW_TOWER:
            cout << readFile("assets/tower.txt");
            cout << this->player.getRoom()->getName() << endl;
            break;
        case VIEW_ROOM:
            cout << readFile("assets/room.txt");
            break;
        case VIEW_INVENTORY:
            cout << "\n\n\nYOUR INVENTORY\n\n\n" << endl;
            break;
    }
}

void Game::command() {
    // Anatomy of a command:
    //     command    argument can be multiple words
    //     \_____/    \____________________________/

    int index;
    string command = "";
    string argument = "";

    string input = toLower(readInput("//> "));
    if ((index = input.find(' ')) == string::npos) {
        // Command only
        command = input.substr(0, index);
    } else {
        // Command with arguments
        command = input.substr(0, index);
        argument = input.substr(index + 1);
    }

    if (command == "exit") {
        this->gameOver = true;
    } else if (command == "help") {
        this->showHelpScreen();
    } else if (command == "view") {
        this->cycleView();
    } else if (command == "tower") {
        this->view = VIEW_TOWER;
    } else if (command == "room") {
        this->view = VIEW_ROOM;
    } else if (command == "inventory") {
        this->view = VIEW_INVENTORY;
    } else if (command == "left") {
        this->player.move(DIR_LEFT);
    } else if (command == "right") {
        this->player.move(DIR_RIGHT);
    } else if (command == "up") {
        this->player.move(DIR_UP);
    } else if (command == "down") {
        this->player.move(DIR_DOWN);
    } else {
        this->command();  // Invalid command. Repeat
    }
}

// Cycle through all the different views
void Game::cycleView() {
    if (this->view < VIEW_COUNT - 1) {
        this->view += 1;
    } else {
        this->view = 0;
    }
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

bool Game::getFoundKiller() {
    return this->foundKiller;
}

void Game::createRooms() {
    // Load and append rooms
    // TODO: Load rooms from text file
    this->rooms.push_back(Room("CONTROL CENTER", "nice place", "XXX"));
    this->rooms.push_back(Room("OFFICE", "nice place", "XXX"));
    this->rooms.push_back(Room("SPA", "nice place", "XXX"));
    this->rooms.push_back(Room("LABORATORY", "nice place", "XXX"));
    this->rooms.push_back(Room("LIBRARY", "nice place", "XXX"));
    this->rooms.push_back(Room("GIFT SHOP", "nice place", "XXX"));
    this->rooms.push_back(Room("CAFETARIA", "nice place", "XXX"));
    this->rooms.push_back(Room("LOBBY", "nice place", "XXX"));
    this->rooms.push_back(Room("TOILET", "nice place", "XXX"));
    this->rooms.push_back(Room("SERVER ROOM", "nice place", "XXX"));
    this->rooms.push_back(Room("CAR PARK", "nice place", "XXX"));
    this->rooms.push_back(Room("PLUMBING ROOM", "nice place", "XXX"));

    // Set room neighbours
    // for each room in rooms, set its left, right, up and down neighbouring
    // room if possible (not wall)
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

void Game::renderTower() {
    vector<string> output;

    // Append roof
    output.push_back("   +-----------------------------------------------------------------------+   ");
    output.push_back("  /                                                                         \\  ");
    output.push_back(" /                            B R U M P   T O W E R                          \\ ");
    output.push_back("|                                                                             |");
    output.push_back("+-----------------------------------------------------------------------------+");

    // Append each room floor by floor
    for (int row = 0; row < ROOM_ROWS; row++) {
        for (int col = 0; col < ROOM_COLS; col++) {
        }
    }
}
