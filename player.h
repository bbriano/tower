/************************************************************
 *
 * player.h
 *
 * Represents the player (detective)
 *
************************************************************/

#pragma once
#include <string>
#include <vector>
#include "item.h"
#include "room.h"

class Player {
    public:
        Player();
        Player(std::string name, Room *startingRoom);
        std::string getName();
        std::vector<std::string> getImage();
        Room * getRoom();
        void move(Direction direction);

    private:
        std::string name;
        std::vector<std::string> image;
        Room *room;
};
