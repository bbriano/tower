/************************************************************
 *
 * main.cpp
 *
 * Main application file
 * Controls the flow of the application
 * Menu option
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#include "game.h"
#include "utils.h"
#include <iostream>
#include <ctime>

using namespace std;

void mainMenu();
void runGame();
void changeDifficulty();
void showLeaderboard();

bool hasExit = false;
Difficulty difficulty = DIFF_EASY;

// Function call graph: main -> mainMenu -> startGame
int main() {
    // Seed random with current time
    srand(time(NULL));

    // Run main menu until the user exits
    while (!hasExit) {
        mainMenu();
    }
}

// Show list of actions to user, run specific actions based on what the user
// input
void mainMenu() {
    // Display main menu screen
    clearScreen();
    cout << readFile("assets/main_menu.txt");

    // Print current difficulty level
    cout << "Difficulty: ";
    switch (difficulty) {
        case DIFF_EASY:
            cout << "Easy" << endl;
            break;
        case DIFF_MEDIUM:
            cout << "Medium" << endl;
            break;
        case DIFF_HARD:
            cout << "Hard" << endl;
            break;
        case DIFF_NIGHTMARE:
            cout << "Nightmare" << endl;
            break;
    }

    // Get option from user. keep asking until get valid option
    /* string input; */
    int option;
    do {
        option = readInputInt("Pick one option (1-4): ");
    } while(option < 1 || option > 4);

    // Call the appropriate functions based on option the user selects
    switch (option) {
        case 1:
            runGame();
            break;
        case 2:
            changeDifficulty();
            break;
        case 3:
            showLeaderboard();
            break;
        case 4:
            hasExit = true;
    }
}

// Start game
void runGame() {
    // Get player name from user. Ask again if user put blank
    string playerName;
    do {
        playerName = readInput("Enter player name: ");
    } while (playerName == "");

    // Run the game while keeping track of the time
    int gameStartTimeSeconds = time(NULL);
    Game game(playerName, difficulty);

    // Show story line and help screen before running the main game loop
    game.showStoryLine();
    game.showHelpScreen();

    // Main game loop
    while (!game.getGameOver()) {
        game.displayView();
        game.command();
    }

    // Display end screen congratulating or ridiculing the player
    // depending on if they win or lose. Show time played
    clearScreen();
    if (game.getFoundKiller()) {
        cout << readFile("assets/you_win.txt");
    } else {
        cout << readFile("assets/game_over.txt");
    }

    int playedTimeSeconds = time(NULL) - gameStartTimeSeconds;
    cout << "TIME: " << toHourMinuteSeconds(playedTimeSeconds) << endl;
    pause();
}

// Show the difficulty options to the player than prompt the player to pick one difficulty level
void changeDifficulty() {
    // Display difficulty options
    clearScreen();
    cout << readFile("assets/difficulty_options.txt");

    // Get a valid option from user. Keep asking until user input valid option
    int option;
    do {
        option = readInputInt("Pick an option (1-4):");
    } while (option < 1 || option > 4);

    // TODO: try to do without iffing. use the Enum
    if (option == 1) {
        difficulty = DIFF_EASY;
    } else if (option == 2) {
        difficulty = DIFF_MEDIUM;
    } else if (option == 3) {
        difficulty = DIFF_HARD;
    } else if (option == 4) {
        difficulty = DIFF_NIGHTMARE;
    }
}

// Display leaderboard. Wait for user before continuing
// TODO: Show leaderboard instead of help screen
void showLeaderboard() {
    clearScreen();
    cout << readFile("assets/help_screen.txt");
    pause();
}
