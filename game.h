/************************************************************
 *
 * game.h
 *
 * Holds the game state
 * Controls the flow of the game
 *
************************************************************/

#pragma once
#include "player.h"
#include "suspect.h"
#include "room.h"
#include "item.h"
#include <string>
#include <vector>

enum View {
    VIEW_TOWER,
    VIEW_ROOM,
    VIEW_COUNT
};

class Game {
    public:
        Game(std::string playerName);

        bool runGameLoop();  // returns true if the player found the killer

    private:
        Player player;
        std::vector<Room> rooms;

        bool gameOver;
        bool foundKiller;
        int view;

        void renderView();
        void cycleView();
        void command();  // Read command from user and do appropriate actions

        void showStoryLine();
        void showHelpScreen();
};
