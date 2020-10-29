/************************************************************
 *
 * room.h
 *
 * May containt suspects and items
 *
************************************************************/

#pragma once
#include <string>
#include <vector>
#include <map>

enum Direction {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
};

class Room {
    public:
        Room();
        Room(std::string name);
        Room(std::string name, std::string imagePath);

        std::string getName();
        std::string getImage();
        bool getItemHidden();
        void search();
        void addBlood();

        // Neighbour
        void setNeighbour(Direction direction, Room *room);
        Room *getNeighbour(Direction direction);

    private:
        std::string name;
        std::string image;
        bool itemHidden;
        std::map<Direction, Room*> neighbour;  // Pointer to neighbouring room in all four direction
};
