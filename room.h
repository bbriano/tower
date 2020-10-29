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
    public:
        Room(std::string name, std::string imagePath);

        std::string getName();
        std::string getImage();
        bool getItemHidden();
        void search();
        void setMurderRoom();

        // Items
        void addItem(Item item);
        void removeItem(int index);
        std::vector<Item> getItems();
        int searchItem(std::string itemName);

        // Suspects
        void addSuspect(Suspect *suspect);
        void removeSuspect(int index);
        std::vector<Suspect*> getSuspects();
        int searchSuspect(std::string suspectName);

        // Neighbour
        void setNeighbour(Direction direction, Room *room);
        Room *getNeighbour(Direction direction);

    private:
        std::string name;
        std::string image;
        bool itemHidden;

        // List of all suspects in the room
        std::vector<Suspect*> suspects;

        // List of all items in the room
        std::vector<Item> items;

        // Pointer to neighbouring room in all four direction
        std::map<Direction, Room*> neighbour;
};
