#include <string>
#include "game.h"

void mainMenu();
void runGame();
void changeDifficulty();
void showLeaderboard();
void addToLeaderboard(int timeSeconds, std::string playerName);
std::string difficultyString();
std::string leaderboardFileName();
