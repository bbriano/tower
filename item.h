/************************************************************
 *
 * item.h
 *
 * Represents an item object
 *
************************************************************/

#pragma once
#include <string>
#include "room.h"

class Item {
    public:
        Item(std::string name, std::string imagePath);
        std::string getName();
        std::string getImage();
        Room *getRoom();
        void setRoom(Room *room);
        void addBlood();

    private:
        std::string name;
        std::string image;
        Room *room;
};
