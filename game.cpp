#include "game.h"
#include "player.h"
#include "utils.h"
#include <iostream>

using namespace std;
string readFile(string fileName);
string readInput(string prompt);

Game::Game(string playerName) {
    // Create and allocate rooms
    // TODO: Need to add more rooms
    this->rooms.push_back(Room("Lobby", "Nice place to sit", "XXX"));
    this->rooms.push_back(Room("Office", "Get that bread sir", "$$$"));

    // Create player instance
    Room startingRoom = this->rooms[0];
    this->player = Player(playerName, &startingRoom);

    // Initialize variables
    this->gameOver = false;
    this->gameOver = false;
    this->view = VIEW_TOWER;

    // Show help screen when first running the game
    this->showStoryLine();
    this->showHelpScreen();
}

// Render view. Read command. Repeat.
// Return true if the killer is found (player won), and false otherwise
bool Game::runGameLoop() {
    while (!gameOver) {
        this->renderView();
        this->command();
    }
    return this->foundKiller;
}

// Draw image to screen
void Game::renderView() {
    clearScreen();
    switch (this->view) {
        case VIEW_TOWER:
            cout << readFile("assets/tower.txt");
            break;
        case VIEW_ROOM:
            cout << readFile("assets/room.txt");
            break;
        case VIEW_COUNT:
            break;
    }
}

void Game::command() {
    // Anatomy of a command:
    //
    //     command   argument
    //        V         V
    //     collect    {item}  <-- What the user types

    int index;
    string command = "";
    string argument = "";

    string input = toLower(readInput("//> "));
    if ((index = input.find(' ')) == string::npos) {
        // Single word command
        command = input.substr(0, index);
    } else {
        // Multi word command
        command = input.substr(0, index);
        argument = input.substr(index + 1);
    }

    if (command == "exit") {
        exit(0);
    } else if (command == "help") {
        this->showHelpScreen();
    } else if (command == "view") {
        this->cycleView();
    } else {
        // Invalid command
        this->command();
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
