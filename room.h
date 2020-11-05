/************************************************************
 *
 * room.h
 *
 * Represents the room object
 * Player, item and suspect all points to a room
 * Can access neighbouring rooms in all 4 directions
 *
 * Briano Goestiawan, 31482228
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
        /* Room(std::string name); */
        Room(std::string name, std::string imagePath);

        std::string getName();
        std::string getImage();
        bool getItemHidden();
        void search();
        bool getMurderRoom();
        void setMurderRoom();

        // Neighbour
        void setNeighbour(Direction direction, Room *room);
        Room *getNeighbour(Direction direction);

    private:
        std::string name;
        std::string image;
        bool itemHidden;
        bool murderRoom;
        std::map<Direction, Room*> neighbour;  // Pointer to neighbouring room in all four direction
};
