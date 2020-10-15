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
    private:
        std::string name;
        std::string description;
        std::string image;

    public:
        Item();
};
