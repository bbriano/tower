/************************************************************
 *
 * room.h
 *
 * May containt suspects and items
 *
************************************************************/

#pragma once
#include <string>
#include <vector>
#include <map>
#include "suspect.h"
#include "item.h"

enum Direction {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
};

class Room {
    private:
        std::string name;  // must be unique
        std::string description;
        std::string image;

        // List of all suspects in the room
        std::vector<Suspect> suspects;

        // List of all items in the room
        std::vector<Item> items;

        // Pointer to neighbouring room in all four direction
        std::map<Direction, Room*> neighbour;

    public:
        Room(
            std::string name,
            std::string description,
            std::string image
        );

        std::string getName();

        void setNeighbour(Direction direction, Room *room);
        Room *getNeighbour(Direction direction);
};
