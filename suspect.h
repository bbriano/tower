/************************************************************
 *
 * suspect.h
 *
 * Represents a suspect
 *
************************************************************/

#pragma once
#include <string>

enum SuspectType {
    SUS_NORMAL,
    SUS_KILLER,
    SUS_VICTIM
};

class Suspect {
    public:
        Suspect(std::string name, std::string imagePath);
        std::string getName();
        void setType(SuspectType type);
        void setAlibi(Suspect *alibi);
        void talk(std::string playerName);

    private:
        std::string name;
        std::string imagePath;
        SuspectType type;
        Suspect *alibi;
};
