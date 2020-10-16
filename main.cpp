/************************************************************
 *
 * main.cpp
 *
 * Main application file
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
void startGame();
void endGame(bool playerWon, int playedTimeSeconds);
void showLeaderboard();

// Function call graph: main -> mainMenu -> startGame
int main() {
    while (true) {
        mainMenu();
    }
}

// Show list of actions to user, run specific actions based on what the user
// input
void mainMenu() {
    // Display main menu screen
    clearScreen();
    cout << readFile("assets/main_menu.txt");

    // Get option from user. keep asking until get valid option
    string input;
    do {
        input = readInput("Pick one option (1-3): ");
    } while(!isInteger(input) || stoi(input) < 1 || stoi(input) > 3);

    // Call the appropriate functions based on option the user selects
    switch (stoi(input)) {
        case 1:
            startGame();
            break;
        case 2:
            showLeaderboard();
            break;
        case 3:
            exit(0);
    }
}

// Start game
void startGame() {
    string playerName = readInput("Enter player name: ");

    // Run the game while keeping track of the time
    int gameStartTimeSeconds = time(0);
    Game game(playerName);
    bool playerWon = game.getFoundKiller();
    int playedTime = time(0) - gameStartTimeSeconds;

    endGame(playerWon, playedTime);
}

// Display end screen congratulating or ridiculing the player
// depending on if they win or lose. Show time played
void endGame(bool playerWon, int playedTimeSeconds) {
    clearScreen();
    if (playerWon) {
        cout << "Congrats you won!";
    } else {
        cout << readFile("assets/game_over.txt");
    }
    cout << "TIME: " << playedTimeSeconds << "s" << endl;
    pause();
}

// Display leaderboard. Wait for user before continuing
// TODO: Show leaderboard instead of help screen
void showLeaderboard() {
    clearScreen();
    cout << readFile("assets/help_screen.txt");
    pause();
}
