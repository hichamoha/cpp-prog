#include "room.h"
#include <iostream>

namespace camelot {

    // Constructs an empty room with no exits.
    Room::Room() {
    }

    /**
     * Constructs a new room with the specified exits.
     */
    Room::Room(std::shared_ptr<Exit> east, std::shared_ptr<Exit> west, std::shared_ptr<Exit> north, std::shared_ptr<Exit> south)
    //Room::Room(Exit * east, Exit * west, Exit * north, Exit * south) 
        : Inside(east, west, north, south) {
    }

    /*
     * If we give the objects an id directly from this vector there might be a 
     * problem when we try to pick up something that has already been picked up
     * by someone else.
     */
    std::string Room::description() const {
        std::string description = Environment::description();
        description += "   This is a room beneath the kingdom of Camelot !";

        return description;
    }

}
