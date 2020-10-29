/************************************************************
 *
 * item.h
 *
 * Represents an item object
 *
************************************************************/

#pragma once
#include <string>

class Item {
    public:
        Item(std::string name, std::string imagePath);

        std::string getName();

        void display();

    private:
        std::string name;
        std::string imagePath;
};
