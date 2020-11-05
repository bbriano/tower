/************************************************************
 *
 * game.h
 *
 * Stores all game objects
 * Controls the flow of the game
 *
 * Briano Goestiawan, 31482228
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
        std::vector<std::string> notes;
        Player player;
        Room inventory;

        // Private variables
        View view;
        Difficulty difficulty;
        int moveCount;
        int searchCount;
        int questionCount;
        bool gameOver;
        bool gameWin;

        // Helper functions to get object pointers
        std::vector<Item *> getInventory();
        Room *getRandomRoom();
        Room *searchRoom(std::string roomName);
        Suspect *searchSuspect(std::string suspectName);
        Item *searchItem(std::string itemName);
        Suspect *getVictim();
        Suspect *getKiller();
        Room *getMurderRoom();
        Item *getMurderWeapon();

        // Create game objects
        void createRooms();
        void createItems();
        void createSuspects();

        // Display methods
        void displayTower();
        void displayRoom();
        void displayInventory();
        void displayStatusBar();
        void displayItem(Item *item);

        // Command methods
        void cycleView();
        void confirmQuit();
        void invalidCommand();
        void question(std::string suspectName);
        void gather();
        void pickup(std::string itemName);
        void drop(std::string itemName);
        void examine(std::string itemName);
        void accuse(std::string suspectName);
        void move(Direction direction);
        void search();
        void stab(std::string suspectName);
        void note(std::string);
        void examineAll();
};
