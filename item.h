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
        Room *getLocation();
        void setLocation(Room *room);
        void addBlood();

    private:
        std::string name;
        std::string image;
        Room *location;
};
