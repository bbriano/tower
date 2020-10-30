#include <string>
#include "game.h"

void mainMenu();
void runGame();
void changeDifficulty();
void showLeaderboards();
void showLeaderboard(Difficulty difficulty);
void addToLeaderboard(int timeSeconds, std::string playerName);
std::string difficultyString(Difficulty difficulty);
std::string leaderboardFileName(Difficulty difficulty);
