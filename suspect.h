/************************************************************
 *
 * suspect.h
 *
 * Represents the suspects in the game
 * A suspect might be a killer, victim or neither (normal)
 * Provides interface to get and set fields
 *
 * Briano Goestiawan, 31482228
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
        SuspectType getType();
        void setType(SuspectType type);
        void setAlibi(Suspect *alibi);
        void talk(std::string playerName);
        void setRoom(Room *room);
        Room *getRoom();
        void move(Direction direction);

    private:
        std::string name;
        SuspectType type;
        Suspect *alibi;
        Room *room;
};
