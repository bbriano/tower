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
    VIEW_INVENTORY
};

enum Difficulty {
    DIFF_EASY,      // Pickup all items as fast as possible. No time limit
    DIFF_MEDIUM,    // Accuse killer, murder room and weapon
    DIFF_HARD,      // Medium requirments but only have 10 moves
    DIFF_NIGHTMARE  // 3 room search, 3 suspect questions, stab the killer
};

class Game {
    public:
        Game(std::string playerName, Difficulty difficulty);
        void showStoryLine();
        void showHelpScreen();
        void displayView();
        void command();
        bool getGameWin();
        bool getGameOver();

    private:
        // Game objects
        std::vector<Room> rooms;
        std::vector<Item> items;
        std::vector<Suspect> suspects;

        Player player;
        Room inventory;

        Suspect *killer;
        Suspect *victim;
        Room *murderRoom;
        Item *murderWeapon;
        std::vector<std::string> notes;

        View view;
        Difficulty difficulty;
        int moveCount;
        int searchCount;
        int questionCount;
        bool gameOver;
        bool gameWin;

        // Create game objects
        void createRooms();
        void createItems();
        void createSuspects();

        // Game view methods
        void cycleView();
        void displayTower();
        void displayRoom();
        void displayInventory();

        // Utility commands
        void confirmQuit();
        void invalidCommand();

        void question(std::string suspectName);
        void gather();
        Room *getRandomRoom();
        Room *searchRoom(std::string roomName);
        Suspect *searchSuspect(std::string suspectName);
        Item *searchItem(std::string itemName);
        std::vector<Item *> getInventory();
        void pickup(std::string itemName);
        void drop(std::string itemName);
        void examine(std::string itemName);
        void accuse(std::string suspectName);
        void move(Direction direction);
        void search();
        void stab(std::string suspectName);
        void note(std::string);
};
