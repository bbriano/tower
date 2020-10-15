/************************************************************
 *
 * room.h
 *
 * May containt suspects and items
 *
************************************************************/

#pragma once
#include "suspect.h"
#include "item.h"
#include <string>
#include <vector>

class Room {
    public:
        Room(
            std::string name,
            std::string description,
            std::string image
        );

    private:
        std::string name;  // must be unique
        std::string description;
        std::string image;

        // List of all suspects in the room
        std::vector<Suspect> suspects;

        // List of all items in the room
        std::vector<Item> items;
};
