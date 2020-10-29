/************************************************************
 *
 * suspect.h
 *
 * Represents a suspect
 *
************************************************************/

#pragma once
#include <string>
#include "room.h"

enum SuspectType {
    SUS_NORMAL,
    SUS_KILLER,
    SUS_VICTIM
};

class Suspect {
    public:
        Suspect(std::string name);
        std::string getName();
        void setType(SuspectType type);
        void setAlibi(Suspect *alibi);
        void talk(std::string playerName);
        void setRoom(Room *room);
        Room *getRoom();

    private:
        std::string name;
        SuspectType type;
        Suspect *alibi;
        Room *room;
};
