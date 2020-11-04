/************************************************************
 *
 * main.cpp
 *
 * Main application file
 * Controls the flow of the application
 * Menu option, and leaderboard functionality
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#include <iostream>
#include <ctime>
#include <string>
#include "game.h"
#include "utils.h"
#define WINDOW_WIDTH 77   // Not including border
#define WINDOW_HEIGHT 39  // Not including border

using namespace std;

bool hasExit = false;
Difficulty difficulty = DIFF_MEDIUM;

void mainMenu();
void runGame();
void changeDifficulty();
void showLeaderboards();
void showLeaderboard(Difficulty difficulty);
void addToLeaderboard(int timeSeconds, std::string playerName);
std::string difficultyString(Difficulty difficulty);
std::string leaderboardFileName(Difficulty difficulty);

// Function call graph: main -> mainMenu -> startGame
int main() {
    // Seed random with current time
    srand(time(NULL));

    // Run main menu until the user exits
    while (!hasExit) {
        mainMenu();
    }
}

// Show list of actions to user, run specific actions based on what the user input
void mainMenu() {
    clearScreen();

    // Display main menu screen
    cout << readFile("assets/cover_screen.txt");
    string diff = fixedWidth(difficultyString(difficulty), ' ', 14);
    cout << "|                                      |                                      |" << endl;
    cout << "|  1. Start game                       |  3. Show leaderboard                 |" << endl;
    cout << "|                                      |                                      |" << endl;
    cout << "|  2. Change difficulty " << diff << " |  4. Exit                             |" << endl;
    cout << "|                                      |                                      |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;

    // Get option from user. keep asking until get valid option
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
            showLeaderboards();
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
    if (game.getGameWin()) {
        cout << readFile("assets/you_win.txt");
    } else {
        cout << readFile("assets/game_over.txt");
    }

    // Display the time played
    int playedTimeSeconds = time(NULL) - gameStartTimeSeconds;
    cout << "|                                                                             |" << endl;
    cout << '|' + fixedWidth("  TIME: " + toHourMinuteSeconds(playedTimeSeconds), ' ', WINDOW_WIDTH) << '|' << endl;
    cout << "|                                                                             |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    pause();

    // Add time to leaderboard if win
    if (game.getGameWin()) addToLeaderboard(playedTimeSeconds, playerName);
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

    // Set difficulty based on user input
    difficulty = static_cast<Difficulty>(option - 1);
}

// Show all leaderboards one by one
void showLeaderboards() {
    showLeaderboard(DIFF_EASY);
    showLeaderboard(DIFF_MEDIUM);
    showLeaderboard(DIFF_HARD);
    showLeaderboard(DIFF_NIGHTMARE);
}

// Display leaderboard. Wait for user before continuing
void showLeaderboard(Difficulty difficulty) {
    clearScreen();
    cout << "+-----------------------------------------------------------------------------+" << endl;

    vector<string> leaderboard = stringSplit(readFile(leaderboardFileName(difficulty)), '\n');

    cout << "|                                                                             |" << endl;
    cout << '|' << fixedWidth("  LEADERBOARD " + difficultyString(difficulty), ' ', WINDOW_WIDTH) << '|' << endl;

    for (int i = 0; i < leaderboard.size(); i++) {
        int spaceIndex = leaderboard[i].find(' ');
        string time = toHourMinuteSeconds(stoi(leaderboard[i].substr(0, spaceIndex)));
        string playerName = leaderboard[i].substr(spaceIndex + 1);

        int dotCount = WINDOW_WIDTH - playerName.length() - time.length() - 6;
        cout << "|                                                                             |" << endl;
        cout << "|  " << playerName << ' ' << fixedWidth("", '.', dotCount) << ' ' << time << "  |" << endl;
    }

    int blankLineCount = WINDOW_HEIGHT - leaderboard.size() * 2 - 2;
    for (int i = 0; i < blankLineCount; i++) {
        cout << "|                                                                             |" << endl;
    }

    cout << "+-----------------------------------------------------------------------------+" << endl;
    pause();
}

// Add a new entry to leaderboard, insert in correct positon sorted in ascending order by time
void addToLeaderboard(int timeSeconds, string playerName) {
    vector<string> leaderboard = stringSplit(readFile(leaderboardFileName(difficulty)), '\n');
    string entry = to_string(timeSeconds) + ' ' + playerName;

    if (leaderboard.size() > 0) {
        // If leaderboard is not empty, insert entry to correct location
        for (int i = 0; i < leaderboard.size(); i++) {
            int spaceIndex = leaderboard[i].find(' ');
            int time = stoi(leaderboard[i].substr(0, spaceIndex));
            if (timeSeconds < time) {
                leaderboard.insert(leaderboard.begin() + i, entry);
                break;
            }
        }
    } else {
        // Else append to leaderboard as first entry
        leaderboard.push_back(entry);
    }

    writeFile(leaderboardFileName(difficulty), stringJoin(leaderboard));
}

string difficultyString(Difficulty difficulty) {
    switch (difficulty) {
        case DIFF_EASY:
            return "[EASY]";
        case DIFF_MEDIUM:
            return "[MEDIUM]";
        case DIFF_HARD:
            return "[HARD]";
        case DIFF_NIGHTMARE:
            return "[NIGTHMARE]";
    }
}

string leaderboardFileName(Difficulty difficulty) {
    switch (difficulty) {
        case DIFF_EASY:
           return "assets/leaderboard_easy.txt";
        case DIFF_MEDIUM:
           return "assets/leaderboard_medium.txt";
        case DIFF_HARD:
            return "assets/leaderboard_hard.txt";
        case DIFF_NIGHTMARE:
            return "assets/leaderboard_nightmare.txt";
    }
}
