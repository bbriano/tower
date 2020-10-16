/************************************************************
 *
 * player.h
 *
 * Represents the player (detective)
 *
************************************************************/

#pragma once
#include <string>
#include <vector>
#include "item.h"
#include "room.h"

class Player {
    public:
        Player();
        Player(std::string name, Room *startingRoom);

        // Accessor methods
        std::string getName();
        std::vector<Item> getInventory();
        Room *getRoom();

        void move(Direction direction);

    private:
        std::string name;
        std::vector<Item> inventory;
        Room *room;

};
