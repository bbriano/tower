/************************************************************
 *
 * suspect.h
 *
 * Represents a suspect
 *
************************************************************/

#pragma once
#include <string>

class Suspect {
    private:
        std::string name;
        std::string description;
        std::string image;

    public:
        Suspect();
};
