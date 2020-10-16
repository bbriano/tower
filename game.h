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
    VIEW_INVENTORY,
    VIEW_COUNT
};

class Game {
    public:
        Game(std::string playerName);

        bool getFoundKiller();

    private:
        Player player;
        std::vector<Room> rooms;

        bool gameOver;
        bool foundKiller;
        int view;

        void createRooms();
        void runGameLoop();
        void cycleView();
        void command();  // Read command from user and do appropriate actions

        void renderView();
        void renderTower();

        void showStoryLine();
        void showHelpScreen();
};
