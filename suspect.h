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
    public:
        Suspect(std::string name, std::string imagePath);

    private:
        std::string name;
        std::string imagePath;
};
