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
        // TODO: Ask tutor why this default constructor must exists
        Player();
        Player(std::string name, Room *startingRoom);

        // Accessor methods
        std::string getName();
        std::vector<std::string> getImage();
        std::vector<Item> getInventory();
        Room *getRoom();

        void move(Direction direction);
        void pickupItem(std::string itemName);
        void dropItem(std::string itemName);

    private:
        std::string name;
        std::vector<std::string> image;
        std::vector<Item> inventory;
        Room *room;

};
