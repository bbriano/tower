/************************************************************
 *
 * player.h
 *
 * Represents the player (detective)
 *
************************************************************/

#pragma once
#include "item.h"
#include "room.h"
#include <string>
#include <vector>

class Player {
    public:
        Player();
        Player(std::string name, Room *startingRoom);

        std::string getName();
        std::vector<Item> getInventory();

    private:
        std::string name;
        std::vector<Item> inventory;
        Room *room;
};
